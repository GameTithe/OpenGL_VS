#version 400 core
 
in vec3 color;
in vec2 texCord;
in vec3 normal;
in vec3 curPos;

out vec4 FragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec3 lightPos;
uniform vec4 lightColor;

uniform vec3 cameraPos;

vec4 pointLight()
{	
	vec3 lightVec = lightPos - curPos;
	float dist = length(lightVec);
	float a = 3.0f;
	float b = 0.7f;
	float inten = 1.0f / ( a * dist * dist + b * dist + 1.0f);

	float ambient = 0.2f;
	vec3 n_normal = normalize(normal);

	vec3 lightDir = normalize(lightVec);
	float diffuse = max( dot( lightDir, n_normal) , 0.0f);

	float specularLight = 0.5f;
	vec3 viewDir = normalize(cameraPos - curPos);
	vec3 reflectDir = reflect(-lightDir, n_normal);

	float specularPow = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specularLight * specularPow;

	 
	//return texture(tex0, texCord) * lightColor * (diffuse + ambient + specular);
	return texture(tex0, texCord) * (  ambient + diffuse *inten + specular * inten) * lightColor;
}
void main()
{ 
	 
	FragColor = pointLight();
}
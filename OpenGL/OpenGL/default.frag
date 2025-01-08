#version 400 core
 
in vec3 color;
in vec2 texCord;

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec4 lightColor;

void main()
{
	//FragColor = vec4(color, 1.0f);

	FragColor = texture(tex0, texCord) * lightColor;
}
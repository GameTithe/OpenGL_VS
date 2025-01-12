 #include <iostream> 
#include <stb/stb_image.h>

#include "OpenGL.h"

#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

#include "Pyramid.h"
#include "Mesh.h"

const float screenHeight = 800;
const float screenWidth = screenHeight * 1.6f;


using namespace std;

Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main()
{
	// openGL init
	glfwInit();

	// verion
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	 
	//create window
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL", NULL,
		NULL);
	if (window == NULL)
	{
		cout << "Faild Create GLFW Window" << endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);

	//load glad
	gladLoadGL(); 

	glViewport(0, 0, screenWidth, screenHeight);

	//Pyramid 
	//Pyramid frogPyramid; 
	//frogPyramid.Init();

	//Texture textures[2] = {
	//	Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
	//	Texture("planksSpec.png", "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE),
	//};	
	
	Texture textures[]
   {
	   Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
	   Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
   };

	//Floor 
	Shader floorShader("default.vert", "default.frag");     
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices)  / sizeof(Vertex));
	std::vector<GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint)); 
	std::vector<Texture> texs(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh floor(verts, inds, texs);

	// light
	Shader lightShader("light.vert", "light.frag");
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	
	Mesh light(lightVerts, lightInds, texs);

	Camera camera(screenWidth, screenHeight, vec3(0.0f, 1.0f, 2.0f));

	// Uniform  
	vec3 lightPosition = vec3(0.5f, 1.5f, 0.5f);
	vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	//Pyradmid
	/*Shader frogShader = frogPyramid.GetShader();
	{
		frogShader.Activate();

		mat4 objModelMatrix = mat4(1.0f);
		objModelMatrix = translate(objModelMatrix, vec3(-2.0f, -0.2f, 0.0f));
		SetMatrixUniform(frogShader, "modelMatrix", objModelMatrix);
		SetVectorUniform(frogShader, "lightPos", lightPosition);
		SetVectorUniform(frogShader, "lightColor", lightColor);
		SetVectorUniform(frogShader, "cameraPos", camera.Position);

	}*/
	
	// Floor 
	{
		floorShader.Activate();

		mat4 objModelMatrix = mat4(1.0f);
		objModelMatrix = translate(objModelMatrix, vec3(0.0f, 0.0f, 0.0f)) *scale(objModelMatrix, vec3(2.0f, 2.0f, 2.0f));
		SetMatrixUniform(floorShader, "modelMatrix", objModelMatrix);
		SetVectorUniform(floorShader, "lightPos", lightPosition);
		SetVectorUniform(floorShader, "lightColor", lightColor);
		SetVectorUniform(floorShader, "cameraPos", camera.Position);
		  
	}

	// light
	{
		lightShader.Activate();
		mat4 lightModelMatrix = mat4(1.0f);
		lightModelMatrix = translate(lightModelMatrix, lightPosition);

		SetMatrixUniform(lightShader, "modelMatrix", lightModelMatrix);
		SetVectorUniform(lightShader, "lightColor", lightColor);
		 
	}

	glEnable(GL_DEPTH_TEST); const char* version = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << version << std::endl;


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// First : Do Activate Shader AND SETTIGN VALUES

		//camera 
		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		
		//Pyramid
		//frogShader.Activate(); 
		//camera.Matrix(frogShader, "cameraMatrix"); 
		//frogPyramid.Draw();
		 
		//Floor 
		floor.Draw(floorShader, camera);
		light.Draw(lightShader, camera);
  
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	floorShader.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
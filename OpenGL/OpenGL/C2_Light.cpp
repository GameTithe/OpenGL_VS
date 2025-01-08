#include <iostream> 
#include <stb/stb_image.h>

#include "OpenGL.h"

#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

const float screenHeight = 800;
const float screenWidth = screenHeight * 1.6f;


using namespace std;


int main()
{
	// openGL init
	glfwInit();

	// verion
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};

	GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
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

	Shader shaderProgram("default.vert", "default.frag");

	VAO vao1;
	vao1.Bind();

	VBO vbo1(vertices, sizeof(vertices));
	EBO ebo1(indices, sizeof(indices));

	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();
	 
	Texture	texture("frog.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.texUnit(shaderProgram, "tex0", 0);
	texture.Unbind(); 

	// light
	Shader lightShader("light.vert", "light.frag");
	VAO lightVao;
	lightVao.Bind();

	VBO lightVbo(lightVertices, sizeof(lightVertices));
	EBO lightEbo(lightIndices, sizeof(lightIndices));

	lightVao.LinkAttrib(lightVbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);


	// Uniform 
	vec4 lightColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	shaderProgram.Activate();

	mat4 objModelMatrix = mat4(1.0f);
	objModelMatrix = translate(objModelMatrix, vec3(0.0f, -0.2f, 0.0f));
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "modelMatrix"), 
	//	1, GL_FALSE, glm::value_ptr(objModelMatrix));
	//
	
	SetMatrixUniform(shaderProgram, "modelMatrix", objModelMatrix);  
	SetVectorUniform(shaderProgram, "lightColor", lightColor);


	lightShader.Activate();
	mat4 lightModelMatrix = mat4(1.0f);
	lightModelMatrix = translate(lightModelMatrix, vec3(0.5f, 0.3f, 0.5f));

	SetMatrixUniform(lightShader, "modelMatrix", lightModelMatrix); 
	SetVectorUniform(lightShader, "lightColor", lightColor);

	lightVao.Unbind();
	lightVbo.Unbind();
	lightEbo.Unbind();

	glEnable(GL_DEPTH_TEST);

	Camera camera(screenWidth, screenHeight, vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// First : Do Activate Shader AND SETTIGN VALUES

		//camera 
		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		
		// Object
		shaderProgram.Activate();  

		camera.Matrix(shaderProgram, "cameraMatrix");

		vao1.Bind();
		texture.Bind(); 

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		

		// Light
		lightShader.Activate();
		camera.Matrix(lightShader, "cameraMatrix");
		lightVao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	texture.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
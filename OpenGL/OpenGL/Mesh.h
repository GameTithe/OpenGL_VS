#pragma once

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"	



class Mesh
{
public :
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	
	
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO vao; 
	
	void Draw(Shader& shader, Camera camera);

};


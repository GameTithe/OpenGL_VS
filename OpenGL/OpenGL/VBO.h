#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <vector>

using glm::vec2;
using glm::vec3;

struct Vertex
{
	vec3 position;
	vec3 normal;
	vec3 color;
	vec2 texUV; 
};
class VBO
{
public:

	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO();
	VBO(std::vector<Vertex>& vertices);

	void Init(std::vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif
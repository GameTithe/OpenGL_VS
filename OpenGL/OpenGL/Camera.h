#ifndef CAMERA_H
#define CAMERA_H
#include "OpenGL.h"

class Camera
{
public:
	vec3 Position;
	vec3 Orientation = vec3(0.0f, 0.0f, -1.0f);
	vec3 Up = vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;

	float speed = 0.1f;
	float sensitivity = 100.0f;

	Camera(int width, int hieght, vec3 Position);

	void Matrix(float FOVdegree, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
	 
};

#endif

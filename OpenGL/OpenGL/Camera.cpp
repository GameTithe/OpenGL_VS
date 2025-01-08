#include "Camera.h"

Camera::Camera(int width, int hieght, vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdegree, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	
	mat4 view = mat4(1.0f);
	mat4 proj = mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	proj = glm::perspective(glm::radians(FOVdegree), (float)(width) / (height) , nearPlane, farPlane);

	glUniformMatrix4fv(
		glGetUniformLocation(shader.ID, uniform),
		1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* window)
{
	
}

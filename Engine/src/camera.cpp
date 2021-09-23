#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "camera.h"
#include "gtc/matrix_transform.hpp"
#include "mat4x4.hpp"
#include "gtc/type_ptr.hpp"

using namespace Engine;

Camera::Camera(Renderer* renderer, ProjectionType type){
	_renderer = renderer;
	_view = glm::mat4(1.0);
	_projection = glm::mat4(1.0);
	_type = type;
}

Camera::~Camera(){
}

void Camera::SetView(glm::vec3 direction, glm::vec3 up){
	_view = glm::lookAt(direction, transform.position, up);
}

void Camera::SetProjection(ProjectionType type){
	_type = type;
	switch (_type)
	{
	case ProjectionType::orthographic:
		_projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.01f, 100.0f);
		break;
	case ProjectionType::perspective:
		_projection = glm::perspective(glm::radians(45.0f), GLfloat(800.0f) / GLfloat(600.0f), 0.01f, 100.0f);
		break;
	default:
		break;
	}
}

void Camera::Init(Shader& shader){
	unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");
	unsigned int projLoc = glGetUniformLocation(shader.GetID(), "projection");
	shader.Use();
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(GetModel()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(GetProjection()));
}

glm::mat4 Camera::GetView(){
	return _view;
}

glm::mat4 Camera::GetProjection(){
	return _projection;
}

ProjectionType Camera::GetProjectionType(){
	return _type;
}

void Camera::Draw(Shader& shader){
	//SetView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//UpdateMatrices();
	_renderer->DrawCamera(shader, GetModel(), GetView());
}

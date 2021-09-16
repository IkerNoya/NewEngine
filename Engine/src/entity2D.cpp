#include "entity2D.h"
#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "ext/scalar_constants.hpp"

using namespace Engine;

void Entity2D::UpdateModel(){
	model.trs = model.translate * model.rotation * model.translate;
}

Entity2D::Entity2D(){
	model.trs = glm::mat4(1.0);
	model.translate = glm::mat4(1.0);
	model.rotation = glm::mat4(1.0);
	model.scale = glm::mat4(1.0);

	transform.position = glm::vec3(1.0);
	transform.rotation = glm::vec3(1.0);
	transform.scale = glm::vec3(1.0);
}

Entity2D::~Entity2D(){

}

void Engine::Entity2D::RotateX(float angle){
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 1.0f;
	axis[1] = 0.0f;
	axis[2] = 0.0f;
	model.rotation = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}

void Engine::Entity2D::RotateY(float angle){
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 0.0f;
	axis[1] = 1.0f;
	axis[2] = 0.0f;
	model.rotation = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}

void Engine::Entity2D::RotateZ(float angle){
	transform.rotation.x = angle;
	glm::vec3 axis = glm::vec3(1.0);
	axis[0] = 0.0f;
	axis[1] = 0.0f;
	axis[2] = 1.0f;
	model.rotation = glm::rotate(glm::mat4(1.0), angle, axis);
	UpdateModel();
}



void Entity2D::Translate(float x, float y, float z){
	transform.position.x += x;
	transform.position.y += y;
	transform.position.z += z;

	model.translate = glm::translate(glm::mat4(1.0), transform.position);
	UpdateModel();
}


void Entity2D::Scale(float x, float y, float z){
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;
	
	model.scale = glm::scale(glm::mat4(1.0), transform.scale);
	UpdateModel();
}

glm::mat4 Entity2D::GetModel() {
	return model.trs	;
}


#include "entity2D.h"


using namespace Engine;

void Entity2D::UpdateModel(){
	My:Matrix4x4::TRS(model, translate, rotate, scale);
}

Entity2D::Entity2D(){
	model = My::Matrix4x4::zero;
	translate = My::Matrix4x4::zero;
	rotate = My::Matrix4x4::zero;
	scale = My::Matrix4x4::zero;

	transform.position = My::Vector3::zero;
	transform.rotation = My::Quaternion::identity;
	transform.localScale = My::Vector3::zero;
}

Entity2D::~Entity2D(){

}

void Entity2D::Rotate(float x, float y, float z){
	transform.rotation.x = x;
	transform.rotation.x = y;
	transform.rotation.z = z;

	rotate = My::Matrix4x4::Rotate(rotate, transform.rotation);
	UpdateModel();
}

void Entity2D::Translate(float x, float y, float z){
	transform.position.x += x;
	transform.position.y += y;
	transform.position.z += z;

	translate = My::Matrix4x4::Translate(translate, transform.position);
	UpdateModel();
}


void Entity2D::Scale(float x, float y, float z){
	transform.localScale.x = x;
	transform.localScale.y = y;
	transform.localScale.z = z;
	
	scale = My::Matrix4x4::Scale(scale, transform.localScale);
	UpdateModel();
}

My::Matrix4x4 Entity2D::GetModel() {
	return model;
}


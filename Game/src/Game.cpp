#include "Game.h"

Game::Game() {

}
Game::~Game() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
	if (!shapes.empty()) {
		for (int i = 0; i < shapes.size(); i++) {
			if (shapes[i]) {
				delete shapes[i];
				_shape = NULL;
			}
		}
		shapes.clear();
	}
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
}
void Game::InitGame() {
	_shape = new Engine::Shape(Type::triangle, GetRenderer(), basicShader);
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::triangle, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));
	//_sprite = new Sprite(false, TypeSprite::quad, GetRenderer(), "holi");
	_sprite->Init(basicShader);
	_shape->Init();
	_shape->Scale(100.0f,100.0f,1.0f);
	_sprite->Scale(100.0f, 100.0f, 100.0f);
	_shape->transform.position = glm::vec3(200.0f, 300.0f, 0);
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]) {
			shapes[i]->Init();
			shapes[i]->Scale(100.0f, 100.0f, 0.0f);
		}
	}
	//ahora se pueden mover las cosas estilo unity
	shapes[0]->transform.position = glm::vec3(600.0f, 300.0f, 0.0f);
	shapes[0]->Color(glm::vec3(0.5f,0.0f,1.0f));
	shapes[1]->transform.position = glm::vec3(400.0f, 100.0f, 0.0f);
	shapes[1]->Color(0.7f,0.3f,0.0f);
	shapes[2]->transform.position = glm::vec3(400.0f, 500.0f, 0.0f);
	shapePos = _shape->transform.position;
}
void Game::UpdateGame() {

	if (input.GetKey(KeyCode::SPACE))
	{
		 shapePos = shapes[1]->transform.position;
		 t = 0;
	}
	
	glm::vec2 newPos = _shape->Lerp(_shape->transform.position, shapePos, t);
	_shape->transform.position = glm::vec3(newPos.x, newPos.y, 0);
	if (input.GetKey(KeyCode::UP)) {
		_shape->transform.scale.x += 2;
		_shape->transform.scale.y += 2;
	}
	if (input.GetKey(KeyCode::DOWN)) {
		_shape->transform.scale.x -= 2;
		_shape->transform.scale.y -= 2;
	}
	angle -= 0.01f;
	t += 0.001f;
	if (t >= 1) t = 0;
	//_shape->RotateZ(angle);
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]){
			shapes[i]->RotateZ(angle);
			shapes[i]->Draw();
		}
	}
	_shape->Draw();
	_sprite->DrawSprite(basicShader);
}
void Game::UnloadGame() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
	if (!shapes.empty()) {
		for (int i = 0; i < shapes.size(); i++) {
			if (shapes[i]) {
				delete shapes[i];
				_shape = NULL;
			}
		}
		shapes.clear();
	}
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}
}
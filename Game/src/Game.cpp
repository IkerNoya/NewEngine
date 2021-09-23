#include "Game.h"

Game::Game() {

}
Game::~Game() {
	if (_shape) {
		delete _shape;
		_shape = NULL;
	}
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]) {
			delete shapes[i];
			_shape = NULL;
		}
	}
}
void Game::Init() {
	_shape = new Engine::Shape(Type::triangle, GetRenderer(), basicShader);
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::triangle, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));
	_shape->Init();
	_shape->Scale(100.0f,100.0f,0.0f);
	_shape->Translate(100.0f, 300.0f, 0);
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]) {
			shapes[i]->Init();
			shapes[i]->Scale(100.0f, 100.0f, 0.0f);
		}
	}
	shapes[0]->Translate(500.0f, 300.0f, 0.0f);
	shapes[1]->Translate(300.0f, 100.0f, 0.0f);
	shapes[2]->Translate(300.0f, 500.0f, 0.0f);
}
void Game::Update() {
	angle -= 0.1f;
	_shape->RotateZ(angle);
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]){
			shapes[i]->RotateZ(angle);
			shapes[i]->Draw();
		}
	}
	_shape->Draw();
}
void Game::Unload() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
}
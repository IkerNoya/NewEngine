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
	_shape = new Engine::Shape(Type::triangle, _renderer, basicShader);
	shapes.push_back(new Shape(Type::quad, _renderer, basicShader));
	shapes.push_back(new Shape(Type::triangle, _renderer, basicShader));
	shapes.push_back(new Shape(Type::quad, _renderer, basicShader));
	_shape->Init();
	_shape->Scale(0.5f,0.5f,0.5f);
	_shape->Translate(-0.5f, 0, 0);
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]) {
			shapes[i]->Init();
			shapes[i]->Scale(0.5f, 0.5f, 0.5f);
		}
	}
	shapes[0]->Translate(0.5f, 0.0f, 0.0f);
	shapes[1]->Translate(0.0f, 0.5f, 0.0f);
	shapes[2]->Translate(0.0f, -0.5f, 0.0f);
}
void Game::Update() {
	angle -= 0.01f;
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
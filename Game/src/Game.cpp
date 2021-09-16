#include "Game.h"

Game::Game() {

}
Game::~Game() {
	if (_shape) {
		delete _shape;
		_shape = NULL;
	}
}
void Game::Init() {
	_shape = new Engine::Shape(Type::triangle, _renderer, basicShader);
	_shape->Init();
	_shape->Translate(0, 0, 0);
}
void Game::Update() {
	_shape->Draw();
	_shape->RotateZ(angle);
	angle -= 0.01f;
}
void Game::Unload() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
}
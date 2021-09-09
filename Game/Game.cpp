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
}
void Game::Update() {
	_shape->Draw();
}
void Game::Unload() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
}
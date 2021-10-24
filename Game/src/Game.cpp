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
	if (player != NULL) {
		delete player;
		player = NULL;
	}
}
void Game::InitGame() {
	_shape = new Engine::Shape(Type::triangle, GetRenderer(), basicShader);
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::triangle, GetRenderer(), basicShader));
	shapes.push_back(new Shape(Type::quad, GetRenderer(), basicShader));
	_sprite = new Engine::Sprite(true, "res/textures/samurai.png", GetRenderer(), textureShader);
	player = new Animation();

	_sprite->Init();
	_shape->Init();
	player->Init(_sprite, glm::ivec2(6,3));
	player->AddAnimation(0, 6, false); //ataque
	player->AddAnimation(6, 11, false); // bloqueo
	player->AddAnimation(12, 14, true); // idle
	player->SetAnimation(2);
	player->SetAnimationTime(0.75f);

	_shape->Scale(100.0f,100.0f,1.0f);
	_sprite->Scale(100.0f, 100.0f, 1.0f);
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
	_sprite->Color(1.0f, 1.0f, 1.0f);
	_sprite->transform.position = glm::vec3(200,300,0);


}
void Game::UpdateGame() {

	//if (input.GetKey(KeyCode::UP)) {
	//	_shape->transform.scale.x += 2;
	//	_shape->transform.scale.y += 2;
	//}
	//if (input.GetKey(KeyCode::DOWN)) {
	//	_shape->transform.scale.x -= 2;
	//	_shape->transform.scale.y -= 2;
	//}

	if (input.GetKey(KeyCode::UP)) {
		player->SetAnimation(2);
	}
	if (input.GetMouseButton(MouseButtons::LEFT_MOUSE_BUTTON)) {
		player->SetAnimation(0);
	}
	if (input.GetMouseButton(MouseButtons::RIGHT_MOUSE_BUTTON)) {
		player->SetAnimation(1);
	}

	if (!player->GetCurrentAnimation().loop && player->GetCurrentAnimation().hasEnded) {
		player->SetAnimation(2);
	}

	player->UpdateIndex(time);

	//_shape->RotateZ(angle);
	//for (int i = 0; i < shapes.size(); i++) {
	//	if (shapes[i]){
	//		shapes[i]->RotateZ(angle);
	//		shapes[i]->Draw();
	//	}
	//}
	//_shape->Draw();
	_sprite->DrawAnimation(player->GetUVs(player->GetCurrentIndex()));
	//_sprite->DrawSprite();

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
	if (player != NULL) {
		delete player;
		player = NULL;
	}
}
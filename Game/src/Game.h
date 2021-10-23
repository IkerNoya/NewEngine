#ifndef GAME_H
#define GAME_H

#include"base.h" 
#include <vector>

using namespace Engine;

class Game: public Base {
private:
	float angle = 0;
	float t = 0;
	glm::vec2 shapePos;
	Shape* _shape = NULL;
	std::vector<Shape*> shapes;
	Sprite* _sprite = NULL;
	Animation* player;

public:
	Game();
	~Game();
	void InitGame() override;
	void UpdateGame() override;
	void UnloadGame() override;
};

#endif
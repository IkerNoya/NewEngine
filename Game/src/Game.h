#ifndef GAME_H
#define GAME_H

#include"base.h" 

using namespace Engine;

class Game: public Base {
private:
	float angle = 0;
	Shape* _shape = NULL;
public:
	Game();
	~Game();
	void Init() override;
	void Update() override;
	void Unload() override;
};

#endif
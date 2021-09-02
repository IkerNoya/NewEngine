#include "base.h"

class Game : public Engine::Base {
private:

public:
	Game();
	~Game();
	void Init() override;
	void Update() override;
	void Unload() override;
};

Game::Game() {

}

Game::~Game() {

}

void Game::Init() {

}

void Game::Update() {
}

void Game::Unload() {

}

int main() {

	Game* game = new Game();
	if (game)
	{
		game->InitEngine();
		game->Init();
		game->UpdateEngine();
		game->Unload();
		game->UnloadEngine();
	}
	return 0;
}
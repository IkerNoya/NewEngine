#include<iostream>
#include"Game.h"
using namespace std;

int main() {
	Game* game = new Game();
	if (game)
	{
		game->InitEngine();
		game->Init();
		game->UpdateEngine();
		game->Unload();
		game->UnloadEngine();
		delete game;
		game = NULL;
	}
	return 0;
}
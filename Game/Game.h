#ifndef GAME_H
#define GAME_H
class Game{
private:
	//Composicion de objetos de nuestro engine aca
	//por ejemplo Shape, Entity, etc
public:
	Game();
	~Game();
	void InitGame();
	void UpdateGame();
	void UnloadGame();
};

#endif
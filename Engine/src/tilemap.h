#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include <vector>

namespace Engine {
	class CollisionManager;
	class Tile;
	class Sprite;

	class ENGINE_API Tilemap {
	private:
		
		vector<Tile*> tiles;
		Sprite* _tilemap = NULL;

	public:
		Tilemap();
		Tilemap(Sprite* tilemap);
		~Tilemap();
		void CreateTilemap();
		void CreateTilemap(Sprite* tilemap);

	};

}


#endif // !TILEMAP_H


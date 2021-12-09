#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include <vector>
#include <string>

namespace Engine {
	class CollisionManager;
	class Tile;
	class Renderer;
	class Shader;
	class Sprite;
	class Entity2D;

	class ENGINE_API Tilemap {
	private:
		std::vector<Tile*> tiles;
		unsigned int grid;
		

	public:



	};

}


#endif // !TILEMAP_H


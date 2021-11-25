#ifndef TILE_H
#define TILE_H

#include "export.h"
#include "texture_importer.h"
namespace Engine {
	class ENGINE_API Tile {
	public:
		bool isWalkable;
		int index;

		Tile();
		~Tile();
	};
}

#endif // !TILE_H

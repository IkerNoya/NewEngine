#ifndef TILE_H
#define TILE_H

#include "export.h"
#include "texture_importer.h"
#include "glm.hpp"


namespace Engine {
	struct ENGINE_API UVCoords {
		float u;
		float v;
	};

	class ENGINE_API Tile {
	public:
		bool isCollisionable;
		int index;
		UVCoords coords[8];
		Tile();
		Tile(bool isCollisionable, int index);
		~Tile();
		void SetCoords(glm::vec4 uvRect);
	};
}

#endif // !TILE_H

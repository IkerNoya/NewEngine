#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"

#include "sprite.h"
#include "texture_importer.h"
#include "tile.h"

#include <vector>


namespace Engine {
	class ENGINE_API TileMap {
	private:
		TextureImporter* texture;
		std::vector<Tile*> tiles;

		int _height;
		int _width;

	public:
		TileMap();
		~TileMap();
		void Load(const char* filePath);
		void AddTile(int index, bool isWalkable);
	};
}


#endif // !TILEMAP_H

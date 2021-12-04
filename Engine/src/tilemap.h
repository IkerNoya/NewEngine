#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include <vector>

namespace Engine {
	class CollisionManager;
	class Tile;

	class ENGINE_API Tilemap {
	private:
		
		vector<Tile*> tiles;
		vector<Tile**> grid;	

		unsigned int _width;
		unsigned int _height;

		float _tileWidth;
		float _tileHeight;

		Sprite _texture;

		float _imageWidth;
		float _imageHeight;

		float convertedPosX;
		float convertedPosY;

		std::string _path;

	public:
		Tilemap();
		~Tilemap();
		const Tile& tile(unsigned int id);
		void SetTile(const Tile& tile);
		void SetMapTileId(int layer, unsigned int col, unsigned int row, unsigned int id);

		void SetDimensions(float width, float height);
		void SetTileDimensions(float tileWidth, float tileHeight);

		void SetTexture(const Sprite& texture);
		void Draw(Renderer* renderer);

		bool ImportTileMap(std::string file, Renderer* renderer);
		void CheckCollision(Entity2D* other);

	};

}


#endif // !TILEMAP_H


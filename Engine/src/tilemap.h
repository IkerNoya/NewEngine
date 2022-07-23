#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include <vector>
#include <string>
#include <glm.hpp>
#include "shader.h"
#include "Entity2D.h"
#include "collision_manager.h"
#include <memory>

struct TilesIndex {
	int x;
	int y;
	TilesIndex(){}
	TilesIndex(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

namespace Engine {
	class CollisionManager;
	class Tile;
	class Renderer;
	class Shader;
	class Shape;
	class Sprite;
	class TextureImporter;

	class ENGINE_API Tilemap {
	private:
		std::vector<std::vector<std::vector<Tile*>>> tiles;
		std::vector<std::vector<std::vector<int>>> grid;
		glm::ivec2 dims;
		Shader shader;
		TextureImporter* _texture;
		Renderer* _renderer;
		const char* imagePath;
		CollisionManager* collisionManager;
		Tile* currentTile = nullptr;

		int _tileWidth = 0;
		int _tileHeight = 0;
		int tilesAmount = 0;
		int _imageWidth = 0;
		int _imageHeight = 0;

		int rows = 0;
		int columns = 0;
		int layers = 0;

		void LoadTilesFromMap();
	public:
		Tilemap(glm::ivec2 dimension, Shader shader, const char* imagePath, Renderer* renderer);
		~Tilemap();
		void SetImagePath(const char* imagepath);
		void LoadMap(const char* path);
		glm::vec4 GetTileFromID(unsigned int id);
		void Draw();
		bool IsTileWalkable(TilesIndex tile);
		bool IsTileValid(TilesIndex tile);
		void CheckCollisionWithTileMap(Entity2D* player, glm::vec3 actualPosition, float speed);
	};

}


#endif // !TILEMAP_H


#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include <vector>
#include <string>
#include <glm.hpp>
#include "shader.h"
#include "Entity2D.h"

namespace Engine {
	class CollisionManager;
	class Tile;
	class Renderer;
	class Shader;
	class Shape;
	class Sprite;
	class TextureImporter;

	class ENGINE_API Tilemap{
	private:
		std::vector<Tile*> tiles;
		std::vector<std::vector<std::vector<int>>> grid;
		glm::ivec2 dims;
		Shader shader;
		TextureImporter* _texture;
		Renderer* _renderer;
		const char* imagePath;

		int _imageWidth=0;
		int _imageHeight=0;
		int _tileWidth=0;
		int _tileHeight=0;
		int tilesAmmount = 0;

		unsigned int _width;
		unsigned int _height;

		float _positionInX;
		float _positionInY;

		void LoadTilesFromMap();

	public:
		Tilemap(glm::ivec2 dimension, Shader shader, const char* imagePath, Renderer* renderer);
		~Tilemap();
		void SetImagePath(const char* imagepath);
		void LoadMap(const char* path);
		glm::vec4 GetTileFromID(unsigned int id);
		void Draw();
		bool CheckCollisionWithTileMap(Shape* shape);
	};

}


#endif // !TILEMAP_H


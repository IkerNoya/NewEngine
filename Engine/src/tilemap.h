#ifndef TILEMAP_H
#define TILEMAP_H
#include "export.h"
#include <vector>
#include <string>
#include <glm.hpp>
#include "shader.h"

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
		std::vector<std::vector<int>> grid;
		glm::ivec2 dims;
		Shader shader;
		const char* imagePath;

	public:
		Tilemap(glm::ivec2 dimension, Shader shader);
		~Tilemap();
		void SetImagePath(const char* imagepath);
		void LoadMap(const char* path);
		glm::vec4 GetTileFromID(unsigned int id);
		void Draw();
	};

}


#endif // !TILEMAP_H


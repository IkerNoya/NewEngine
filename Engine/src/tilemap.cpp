#include "tilemap.h"
#include "collision_manager.h"
#include "tile.h"
#include "xml_lib/tinyxml2.h"	
#include <sstream>

using namespace Engine;

Tilemap::Tilemap(glm::ivec2 dimensions, Shader shader) {
	dims = dimensions;
	this->shader = shader;
}

Tilemap::~Tilemap() {
	if (!grid.empty()) {
		for (int y = 0; y < grid.size(); y++) {
			for (int x = 0; x < grid[y].size(); x++) {
				grid[y][x] = 0;
			}
		}
		grid.clear();
	}
	if (!tiles.empty()){
		for (int i = 0; i < tiles.size(); i++) {
			if (tiles[i] != NULL) {
				delete tiles[i];
				tiles[i] == NULL;
			}
		}
		tiles.clear();
	}
}

void Tilemap::SetImagePath(const char* imagepath){
	this->imagePath = imagepath;
}

void Tilemap::LoadMap(const char* path) {
	tinyxml2::XMLDocument map;
	map.LoadFile(path);
	tinyxml2::XMLElement* mapElements = map.FirstChildElement("map");
	if (mapElements == NULL) {
		std::cout << "Error loading tilemap" << std::endl;
		return;
	}
	int width = mapElements->IntAttribute("width");
	int height = mapElements->IntAttribute("height");
	grid.resize(height);

	tinyxml2::XMLElement* layerElement = mapElements->FirstChildElement("layer");
	if (layerElement == NULL) {
		std::cout << "Error loading tilemap" << std::endl;
		return;
	}
	tinyxml2::XMLText* dataElement = layerElement->FirstChildElement("data")->FirstChild()->ToText();
	if (dataElement == NULL) {
		std::cout << "Error loading tilemap" << std::endl;
		return;
	}


	int x = 0;
	int y = 0;
	std::string mapGrid;
	mapGrid = dataElement->Value();

	std::stringstream ss(mapGrid);
	for (int y = 0; y < width; y++) {
		grid[y].resize(width);
		for (int x = 0; x < height; x++) {
			std::string value;
			std::getline(ss, value, ',');
			if (!ss.good())
				break;

			int val;
			if (std::stringstream(value) >> val)
				grid[y][x]=val;

		}
	}

	for (int y = 0; y < dims.y; y++) {
		for (int x = 0; x < dims.x; x++) {
			std::cout << grid[x][y] << " , ";
		}
		std::cout<<std::endl;
	}

}

glm::vec4 Tilemap::GetTileFromID(unsigned int id) {
	int xTile = id % dims.x; // se hace para que cuando el indice sea mayor a la dimension en x, vuelva a ser 0, es decir, se "reinicia" el ciclo en x
	int yTile = id / dims.x;
	
	//                      x  y   w   h
	glm::vec4 uv = glm::vec4(0, 0, 0, 0);

	uv.x = xTile / static_cast<float>(dims.x); // X
	uv.y = yTile / static_cast<float>(dims.y); // Y
	uv.z = 1.0f / dims.x; // Ancho / W
	uv.w = 1.0f / dims.y; // Alto / H

	return uv;
}

void Tilemap::Draw() {
	if (!tiles.empty()) {
		for (int i = 0; i < tiles.size(); i++) {
			if (tiles[i] != NULL) {
				tiles[i]->DrawSprite();
			}
		}
	}
}
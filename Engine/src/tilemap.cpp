#include "tilemap.h"
#include "collision_manager.h"
#include "tile.h"
#include "xml_lib/tinyxml2.h"	
#include <sstream>
#include "texture_importer.h"
#include "utils.h"
#include "renderer.h"

using namespace Engine;

Tilemap::Tilemap(glm::ivec2 dimensions, Shader shader, const char* imagePath, Renderer* renderer) {
	dims = dimensions;
	this->shader = shader;
	this->imagePath = imagePath;
	_renderer = renderer;
	_texture = new TextureImporter();
}

Tilemap::~Tilemap() {
	if (_texture)delete _texture; _texture = nullptr;
	if (!grid.empty()) grid.clear();
	if (!tiles.empty()) {
		for (int l = 0; l < tiles.size(); l++) {
			for (int y = 0; y < tiles[l].size(); y++) {
				for (int x = 0; x < tiles[l][y].size(); x++) {
					if (tiles[l][y][x]) {
						delete tiles[l][y][x];
					}
				}
			}
		}
		tiles.clear();
	}
}

void Tilemap::SetImagePath(const char* imagepath) {
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
	_tileWidth = mapElements->IntAttribute("tilewidth");
	_tileHeight = mapElements->IntAttribute("tileheight");

	std::vector<tinyxml2::XMLElement*>layerElement;
	for (tinyxml2::XMLElement* child = mapElements->FirstChildElement(); child; child = child->NextSiblingElement()) {
		string name = child->Name();
		string layer = "layer";
		if (child != NULL && name == layer) {
			layers++;
			layerElement.push_back(child);
		}
	}
	
	std::cout << layers << std::endl;
	grid.resize(layers);
	for (int l = 0; l < grid.size(); l++) {
		tinyxml2::XMLText* dataElement = layerElement[l]->FirstChildElement("data")->FirstChild()->ToText();
		if (dataElement == NULL) {
			std::cout << "Error loading tilemap" << std::endl;
			return;
		}

		std::string mapGrid;
		mapGrid = dataElement->Value();
		std::stringstream ss(mapGrid);
		grid[l].resize(height);
		for (int y = 0; y < height; y++) {
			grid[l][y].resize(width);
			for (int x = 0; x < width; x++) {
				std::string value;
				std::getline(ss, value, ',');
				if (!ss.good())
					break;

				int val;
				if (std::stringstream(value) >> val)
					grid[l][y][x] = val;

				tilesAmount++;
			}
		}
	}
	map.Clear();
	rows = height;
	columns = width;
	LoadTilesFromMap();
}


void Tilemap::LoadTilesFromMap() {
	float initialYPos = 700;
	float initialXPos = _tileWidth;

	float posY = initialYPos;
	float posX = initialXPos;
	float z = 0;
	int actualID = 0;

	tiles.resize(layers);
	for (int l = 0; l < tiles.size(); l++) {
		tiles[l].resize(rows);
		for (int y = 0; y < tiles[l].size(); y++) {
			tiles[l][y].resize(columns);
			for (int x = 0; x < tiles[l][y].size(); x++) {
				int id = grid[l][y][x];
				Tile* tile = nullptr;
				if (l <= 0) {
					tile = new Tile(id, false);
					tile->SetRenderer(_renderer);
					tile->SetShader(shader);
					tile->SetPath(imagePath);
					tile->Init();
					tile->Translate(posX, posY, z);
					tile->Scale(_tileWidth, _tileHeight, 1);
					tile->GetTileProperties("res/tilemap/Ground.tsx");
					tile->SetUVs(GetTileFromID(id));
				}
				else {
					if (id > 0) {
						id -= actualID;
						tile = new Tile(id, false);
						tile->SetRenderer(_renderer);
						tile->SetShader(shader);
						tile->SetPath(imagePath);
						tile->Init();
						tile->Translate(posX, posY, z);
						tile->Scale(_tileWidth, _tileHeight, 1);
						tile->GetTileProperties("res/tilemap/Ground.tsx");
						tile->SetUVs(GetTileFromID(id));
					}
				}
				if(tile)
					tiles[l][y][x] = tile;
				else
					tiles[l][y][x] = nullptr;

				posX += _tileWidth*2;
			}
			posY -= _tileHeight + _tileHeight;
			posX = initialXPos;
		}
		posX = initialXPos;
		posY = initialYPos;
		z += 0.001f;
		actualID = 1;
	}
}

glm::vec4 Tilemap::GetTileFromID(unsigned int id) {
	int xTile = id % dims.x; // se hace para que cuando el indice sea mayor a la dimension en x, vuelva a ser 0, es decir, se "reinicia" el ciclo en x
	int yTile = id / dims.x;
	yTile = _imageHeight - yTile - 1;
	//                      x  y   w   h
	glm::vec4 uv = glm::vec4(0, 0, 0, 0);

	uv.x = xTile / static_cast<float>(dims.x); // X
	uv.y = yTile / static_cast<float>(dims.y); // Y
	uv.z = 1.0f / (dims.x); // Ancho / W
	uv.w = 1.0f / (dims.y); // Alto / H

	return uv;
}

void Tilemap::Draw() {
	//float mapWidth = - (columns * _tileWidth) / 2;
	//float mapHeight = (rows * _tileHeight) / 2;
	if (!tiles.empty()) {
		for (int i = 0; i < tiles.size(); i++) {
			for (int j = 0; j < tiles[i].size(); j++) {
				for (int k = 0; k < tiles[i][j].size(); k++) {
					if (tiles[i][j][k]) {
						//tiles[i][j][k]->transform.position.x = mapWidth + (_tileWidth * k);
						//tiles[i][j][k]->transform.position.x = mapHeight - (_tileHeight * j);
						tiles[i][j][k]->DrawSprite();
					}
				}
			}
		}
	}
}

bool Tilemap::IsTileValid(TilesIndex tile) {
	if (tile.x < 0 || tile.y < 0 || tile.x >= tiles[0][0].size() || tile.y >= tiles[0].size())
		return false;

	for (int i = layers - 1; i >= 0; i--) {
		if (tiles[i][tile.y][tile.x]) {
			if (!tiles[i][tile.y][tile.x]->GetIsWalkable())
				return false;
		}
	}
	return true;
}

void Tilemap::CheckCollisionWithTileMap(Entity2D* player, glm::vec3 actualPosition, float speed) {
	//paso 1: ditancia con punto de origen de tilemap
	float distX = glm::distance(glm::vec2(actualPosition.x, 0), glm::vec2(0, 0));
	float widthDistX = glm::distance(glm::vec2(actualPosition.x + player->transform.scale.x *.5f, 0), glm::vec2(0, 0));
	float distY = glm::distance(glm::vec2(0, actualPosition.y), glm::vec2(0, 700));
	float heightDistance = glm::distance(glm::vec2(0, actualPosition.y - player->transform.scale.y*.5f), glm::vec2(0, 700));

	//paso 2: traducirlo a indices en base a (0,0)
	float xIndex = distX / _tileWidth*0.5f;
	float yIndex = distY/ _tileHeight*0.5f;

	float widthIndex = widthDistX / _tileWidth * 0.5f;
	float heightIndex = heightDistance / _tileHeight * .5f;

	//paso 3: conseguir indices vecinos
	int left = static_cast<int>(xIndex) - 1;
	int up = static_cast<int>(yIndex) - 1;
	int right = static_cast<int>(widthIndex) +1;
	int down = static_cast<int>(heightIndex)+1;

	for (int i = left; i <= right; i++) {
		for (int j = up; j <= down; j++) {
			if (!IsTileValid(TilesIndex(i, j))) {
				collisionManager->CheckCollision(player, tiles[0][j][i], speed);
			}
		}
	}
	std::cout << "horizontal = (" << left << ", " << right << ")" << std::endl;
	std::cout << "vertical = (" << up << ", " << down << ")" << std::endl;
	//std::cout << "Origin index = (" << xIndex << ", " << yIndex << ")" << std::endl;
	//std::cout << "player index = (" << widthIndex << ", " << heightIndex << ")" << std::endl;

}
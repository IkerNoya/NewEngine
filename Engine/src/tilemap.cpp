#include "tilemap.h"
#include "collision_manager.h"
#include "tile.h"
#include "xml_lib/tinyxml2.h"	
#include <sstream>
#include "texture_importer.h"
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
	if (!grid.empty()) {
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
	if (_texture != NULL) {
		delete _texture;
		_texture = NULL;
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
	_tileWidth = mapElements->IntAttribute("tilewidth");
	_tileHeight = mapElements->IntAttribute("tileheight");

	int layers = 0;
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
		for (int y = 0; y < width; y++) {
			grid[l][y].resize(width);
			for (int x = 0; x < height; x++) {
				std::string value;
				std::getline(ss, value, ',');
				if (!ss.good())
					break;

				int val;
				if (std::stringstream(value) >> val)
					grid[l][y][x] = val;

				tilesAmmount++;
			}
		}
	}
	LoadTilesFromMap();
}


void Tilemap::LoadTilesFromMap() {
	_texture->SetPath(imagePath);
	_texture->LoadImage(_imageWidth, _imageHeight, true);
	int xPos = 0;
	int yPos = 720;
	for (int l = 0; l < grid.size(); l++) {
		xPos = 0;
		yPos = 720;
		for (int y = 0; y < grid[l].size(); y++) {
			for (int x = 0; x < grid[l][y].size(); x++) {
				Tile* newTile = new Tile(grid[l][y][x], false);
				newTile->SetRenderer(_renderer);
				newTile->SetShader(shader);
				newTile->SetPath(imagePath);
				newTile->Init();
				newTile->Translate(xPos, yPos, l - 0.5f);
				newTile->Scale(_tileWidth, _tileHeight, 1);
				if (newTile->GetID() <= 0 && l > 0) {
					delete newTile;
					newTile = NULL;
					xPos += _tileWidth + _tileWidth;
				}
				else {
					newTile->SetPropertiesPath("res/tilemap/Ground.tsx");
					newTile->SetUVs(GetTileFromID(newTile->GetID() - 1));
					tiles.push_back(newTile);
					xPos += newTile->transform.scale.x + _tileWidth;
				}

			}
			yPos -= _tileHeight + _tileHeight;
			xPos = 0;
		}
	}
	std::cout << "Ammount of tilemap Entities: " << tiles.size() << endl;
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
	if (!tiles.empty()) {
		for (int i = 0; i < tiles.size(); i++) {
			if (tiles[i] != NULL) {
				tiles[i]->DrawSprite();
				bool test = tiles[i]->GetIsWalkable();

			}
		}
	}
}

bool Tilemap::CheckCollisionWithTileMap(Shape* shape) {
	bool collides = false;
	_positionInX = shape->transform.position.x + (_width / 2) * _tileWidth;
	_positionInY = shape->transform.position.y + (_height / 2) * _tileHeight;

	return collides;
}

//chequea si el shape esta colisionando el tilemap
//bool Tilemap::TileMapCollision(Shape* shape) {
//	if (shape->transform.position.x + shape->transform.scale.x / 2.0f < Entity2D::transform.position.x - _imageWidth / 2.0f ||
//		shape->transform.position.x - shape->transform.scale.x / 2.0f > Entity2D::transform.position.x + _imageWidth / 2.0f ||
//		shape->transform.position.y + shape->transform.scale.y / 2.0f < Entity2D::transform.position.y - _imageHeight / 2.0f ||
//		shape->transform.position.y - shape->transform.scale.y / 2.0f > Entity2D::transform.position.y + _imageHeight / 2.0f)
//		return false;
//	else
//		return true;
//}
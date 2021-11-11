#include "tilemap.h"

using namespace Engine;

TileMap::TileMap() {
	texture = new TextureImporter();
	_width = 0;
	_height = 0;
}
TileMap::~TileMap() {
	if (texture != NULL) {
		delete texture;
		texture = NULL;
	}
	if (!tiles.empty()) {
		for (int i = 0; i < tiles.size(); i++) {
			if (tiles[i] != NULL) {
				delete tiles[i];
				tiles[i] = NULL;
			}
		}
		tiles.clear();
	}
}

void TileMap::Load(const char* filePath) {
	if (texture != NULL) {
		texture->SetPath(filePath);
		texture->LoadImage(_width, _height, true);
	}


}

void TileMap::AddTile(int index, bool isWalkable){
	Tile* tile = new Tile(isWalkable, index);
	tiles.push_back(tile);
}

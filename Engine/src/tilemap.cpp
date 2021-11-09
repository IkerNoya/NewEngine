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
}

void TileMap::Load(const char* filePath) {
	if (texture != NULL) {
		texture->SetPath(filePath);
		texture->LoadImage(_width, _height, true);
	}


}

void TileMap::SetTile(int index, bool isWalkable){
}

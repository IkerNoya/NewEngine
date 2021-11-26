#include "tile.h"
#include "sprite.h"
using namespace Engine;


Tile::Tile() {}

Tile::Tile(Sprite* texture, bool isWalkable) {
	_tile = texture;
	_isWalkable = isWalkable;
}

Tile::~Tile() {
	if (_tile != NULL) {
		delete _tile;
		_tile = NULL;
	}
}

void Tile::SetTexture(Sprite* texture){
	_tile = texture;
}

void Tile::SetIsWalkable(bool value) {
	_isWalkable = value;
}

Sprite* Tile::GetTexture() {
	return _tile;
}

bool Tile::GetIsWalkable() {
	return _isWalkable;
}
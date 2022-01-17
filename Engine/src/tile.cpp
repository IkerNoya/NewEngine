#include "tile.h"
using namespace Engine;


Tile::Tile() {}

Tile::Tile(unsigned int id, bool isWalkable) : Sprite(){
	_id = id;
	_isWalkable = isWalkable;
}

Tile::~Tile() {
}

void Tile::SetIsWalkable(bool value) {
	_isWalkable = value;
}

bool Tile::GetIsWalkable() {
	return _isWalkable;
}

unsigned int Tile::GetID() {
	return _id;
}

void Tile::SetID(unsigned int value) {
	_id = value;
}


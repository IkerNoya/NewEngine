#include "tile.h"

using namespace Engine;

Tile::Tile() {
	isCollisionable = false;
	index = 0;
}
Tile::Tile(bool isCollisionable, int index) {
	this->isCollisionable = isCollisionable;
	this->index = index;
}

Tile::~Tile() {}

void Tile::SetCoords(glm::vec4 uvRect) {
	//				x + ancho                   y + alto
	coords[0].u = uvRect.x + uvRect.z; coords[0].v = uvRect.y + uvRect.w;    // top right
	//				 x + ancho                   y
	coords[1].u = uvRect.x + uvRect.z; coords[1].v = uvRect.y;				 // bottom right
	//				x                  y
	coords[2].u = uvRect.x; coords[2].v = uvRect.y;							// bottom left
	//				x					y + alto
	coords[3].u = uvRect.x; coords[3].v = uvRect.y + uvRect.w;				// top left
}
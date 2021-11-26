#include "tilemap.h"
#include "collision_manager.h"
#include "tile.h"
#include "sprite.h"

using namespace Engine;

Tilemap::Tilemap() {
	_tilemap = NULL;
}

Tilemap::Tilemap(Sprite* tilemap) {
	_tilemap = tilemap;
}

Tilemap::~Tilemap() {

}

void Tilemap::CreateTilemap() {

}

void Tilemap::CreateTilemap(Sprite* tilemap) {

}
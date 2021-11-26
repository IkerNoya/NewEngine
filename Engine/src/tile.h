#ifndef TILE_H
#define TILE_H
#include "export.h"

namespace Engine {

	class Sprite;
	class ENGINE_API Tile {
	private:
		Sprite* _tile = nullptr;
		bool _isWalkable = false;

	public:
		Tile();
		Tile(Sprite* texture, bool isWalkable);
		~Tile();
		void SetTexture(Sprite* texture);
		void SetIsWalkable(bool value);
		Sprite* GetTexture();
		bool GetIsWalkable();
	};

}
#endif // !TILE_H

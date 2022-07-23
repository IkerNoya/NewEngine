#ifndef TILE_H
#define TILE_H
#include "export.h"
#include "sprite.h"
#include <vector>

namespace Engine {

	class ENGINE_API Tile : public Sprite {
	private:
		bool _isWalkable = false;
		bool _wasInitialized = false;
		unsigned int _id = 0;
		std::vector<Tile*> _adyacentTiles;

	public:
		Tile();
		Tile(unsigned int id, bool isWalkable);
		~Tile();
		void SetIsWalkable(bool value);
		bool GetIsWalkable();
		unsigned int GetID();
		void SetID(unsigned int value);
		void GetTileProperties(const char* path);
		inline bool WasInitialized() const { return _wasInitialized; }
	};

}
#endif // !TILE_H

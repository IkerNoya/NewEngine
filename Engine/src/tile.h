#ifndef TILE_H
#define TILE_H
#include "export.h"
#include "sprite.h"

namespace Engine {

	class ENGINE_API Tile : public Sprite {
	private:
		bool _isWalkable = false;
		unsigned int _id = 0;

	public:
		Tile();
		Tile(unsigned int id, bool isWalkable);
		~Tile();
		void SetIsWalkable(bool value);
		bool GetIsWalkable();
		unsigned int GetID();
		void SetID(unsigned int value);
	};

}
#endif // !TILE_H

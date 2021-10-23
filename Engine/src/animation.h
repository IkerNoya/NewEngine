#ifndef ANIMATION_H
#define ANIMATION_H
#include "export.h"
#include "glm.hpp"
namespace Engine {

	class Sprite;
	class ENGINE_API Animation {
		Sprite* sprite;
		glm::ivec2 dimensions;
	public:
		Animation();
		~Animation();
		void Init(Sprite* texture, const glm::ivec2& tileDims);
		glm::vec4 GetUVs(int index);

	};

}
#endif // !ANIMATION_H


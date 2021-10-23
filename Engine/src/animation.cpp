#include "animation.h"

Engine::Animation::Animation(){
	sprite = NULL;
	dimensions = glm::ivec2(0, 0);
}

Engine::Animation::~Animation(){
	if (sprite != NULL){
		delete sprite;
		sprite = NULL;
	}
}

void Engine::Animation::Init(Sprite* texture, const glm::ivec2& tileDims){
	sprite = texture;
	dimensions = tileDims;

}

glm::vec4 Engine::Animation::GetUVs(int index){
	int xTile = index % dimensions.x;
	int yTile = index / dimensions.x;
	glm::vec4 uv = glm::vec4(0,0,0,0);
	uv.x = xTile / static_cast<float>(dimensions.x);
	uv.y = yTile / static_cast<float>(dimensions.y);
	uv.z = 1.0f / dimensions.x;
	uv.w = 1.0f / dimensions.y;
	return uv;
}

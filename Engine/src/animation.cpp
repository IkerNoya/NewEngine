#include "animation.h"
#include "time_manager.h"
#include <iostream>

Engine::Animation::Animation() {
	sprite = NULL;
	dimensions = glm::ivec2(0, 0);
	state = AnimationState::idle;
}

Engine::Animation::~Animation() {
}

void Engine::Animation::Init(Sprite* texture, const glm::ivec2& tileDims) {
	sprite = texture;
	dimensions = tileDims;

}

glm::vec4 Engine::Animation::GetUVs(int index) {
	int xTile = index % dimensions.x;
	int yTile = index / dimensions.x;
	glm::vec4 uv = glm::vec4(0, 0, 0, 0);
	uv.x = xTile / static_cast<float>(dimensions.x);
	uv.y = yTile / static_cast<float>(dimensions.y);
	uv.z = 1.0f / dimensions.x;
	uv.w = 1.0f / dimensions.y;
	return uv;
}

void Engine::Animation::UpdateIndex(Time& time) {

	int framesAmmount = (animation[_currentAnimation]._endIndex) - animation[_currentAnimation]._beginIndex;

	if (!animation[_currentAnimation].hasEnded) {
		_actualCurrentIndex = animation[_currentAnimation]._beginIndex;

		_actualCurrentIndex = _actualCurrentIndex + static_cast<int>(_currentTime) % framesAmmount;

		if (!animation[_currentAnimation].loop && _actualCurrentIndex >= animation[_currentAnimation]._endIndex-1) {
			_actualCurrentIndex = animation[_currentAnimation]._endIndex-1;
			animation[_currentAnimation].hasEnded = true;
		}
	}
	else {
		_actualCurrentIndex = animation[_currentAnimation]._endIndex -1;
	}

	_currentTime += time.GetDeltaTime() * animationSpeed;
}

void Engine::Animation::SetAnimationTime(float time) {
	if (time < 0)
		time *= -1;

	animationSpeed = time * 10;
}

int Engine::Animation::GetCurrentIndex() {
	return _actualCurrentIndex;
}

void Engine::Animation::AddAnimation(int beginIndex, int endIndex, bool isLoopable) {
	AnimationData newAnim;
	newAnim._beginIndex = beginIndex;
	newAnim._endIndex = endIndex;
	newAnim.loop = isLoopable;
	animation.push_back(newAnim);
}

Engine::AnimationData Engine::Animation::GetCurrentAnimation() {
	return animation[_currentAnimation];
}

void Engine::Animation::SetAnimation(int index) {
	_currentTime = 0;
	_currentAnimation = index;
	_firstIndex = animation[_currentAnimation]._beginIndex;
	_lastIndex = animation[_currentAnimation]._endIndex;

	if (_currentIndex < _firstIndex || _currentIndex > _lastIndex)
		_actualCurrentIndex = _firstIndex;

	animation[_currentAnimation].hasEnded = false;
}


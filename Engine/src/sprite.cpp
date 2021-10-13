#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"sprite.h"

namespace Engine {
	Sprite::Sprite(bool transparency, Type type, Renderer* renderer, std::string name) {

	}

	Sprite::Sprite(bool transparency, const char* path, Type type, Renderer* renderer, std::string name) {

	}

	Sprite::Sprite(int width, int height, const char* path, bool transparency, Type type, Renderer* renderer, std::string name) {

	}

	Sprite::~Sprite() {

	}

	void Sprite::init(Shader& shader) {

	}

	void Sprite::LoadSprite() {

	}

	void Sprite::LoadSprite(int width, int height) {

	}

	void Sprite::LoadSprite(int width, int height, const char* path) {

	}

	void Sprite::BindTexture() {

	}

	void Sprite::BlendSprite() {
		
	}

	void Sprite::UnBlendSprite() {

	}

	void Sprite::DrawSprite(Shader& shader) {

	}

	void Sprite::SetWidth(int width) {

	}

	int Sprite::GetWidth() {

	}

	void Sprite::SetHeight(int height) {

	}

	int Sprite::GetHeight() {

	}

	void Sprite::SetPath(const char* path) {

	}

	const char* Sprite::GetPath() {

	}
}


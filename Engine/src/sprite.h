#ifndef SPRITE_H
#define SPRITE_H
#include"shape.h"
#include"export.h"
#include"texture_importer.h"

namespace Engine {
	class ENGINE_API Sprite : public Shape {
	private:
		int _width;
		int _height;
		bool _transparency;

		TextureImporter* _texImporter;
	public:
		Sprite(bool transparency, Type type, Renderer* renderer, std::string name);
		Sprite(bool transparency, const char* path, Type type, Renderer* renderer, std::string name);
		Sprite(int width, int height, const char* path, bool transparency, Type type, Renderer* renderer, std::string name);
		~Sprite();
		void init(Shader& shader);
		void LoadSprite();
		void LoadSprite(int width, int height);
		void LoadSprite(int width, int height, const char* path);
		void BindTexture();
		void BlendSprite();
		void UnBlendSprite();
		void DrawSprite(Shader& shader);
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();
		void SetPath(const char* path);
		const char* GetPath();
	};
}

#endif
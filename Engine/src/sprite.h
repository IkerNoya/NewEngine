#ifndef SPRITE_H
#define SPRITE_H
#include"shape.h"
#include"export.h"
#include"texture_importer.h"
#include"renderer.h"

namespace Engine {

	class ENGINE_API Sprite : public Entity2D {
	private:
		int _width;
		int _height;
		bool _transparency;
		Renderer* _renderer;
		TextureImporter* _texImporter;

		unsigned int _vao = 0;
		unsigned int _vbo = 0;
		unsigned int _ebo = 0;

		float _vertices[32] = {
	        	1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  1, 1,
	        	1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  1, 0,
	           -1.0f, -1.0f, 0.0f,  1.0f,1.0f,1.0f,  0, 0,
	           -1.0f,  1.0f, 0.0f,  1.0f,1.0f,1.0f,  0, 1
			};

		unsigned int _quadIndices[6] = {
			0,1,3,
			1,2,3
		};
		Shader shader;

		void GenerateVAO();
		void BindVAO();
		void BindVBO(float* vertices, int AmmountOfVertices);
		void BindEBO(unsigned int* indices, int AmmountOfIndices);
		void UnbindBuffers();
		void DeleteBuffer();
	public:
		Sprite(bool transparency, Renderer* renderer, Shader shader, std::string name);
		Sprite(bool transparency, const char* path,  Renderer* renderer, Shader shader, std::string name);
		Sprite(int width, int height, const char* path, bool transparency, Renderer* renderer, Shader shader, std::string name);
		~Sprite();
		void Init();
		void LoadSprite();
		void LoadSprite(int width, int height);
		void LoadSprite(int width, int height, const char* path);
		void BindBuffers();
		void BindTexture();
		void BlendSprite();
		void UnBlendSprite();
		void Color(float r, float g, float b);
		void Color(glm::vec3 color);
		void DrawSprite();
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();
		void SetPath(const char* path);
		const char* GetPath();
	};
}

#endif
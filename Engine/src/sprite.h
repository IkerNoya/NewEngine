#ifndef SPRITE_H
#define SPRITE_H
#include"shape.h"
#include"export.h"
#include"texture_importer.h"
#include"renderer.h"

namespace Engine {
	enum class ENGINE_API TypeSprite
	{
		triangle, quad
	};

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

		float texQuadVertices[36] = {
			1.0f,  1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  0.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 1.0f,  1.0f,1.0f,1.0f,  0.0f, 1.0f
		};

		float texTriVertices[27] = {
			0.5f,-0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   1.0f,0.0f,
			0.0f, 0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   0.5f,1.0f,
		   -0.5f,-0.5f, 0.0f,1.0f,  1.0f, 1.0f, 1.0f,   0.0f,0.0f
		};

		unsigned int _triIndices[3] = {
			0,1,2
		};

		unsigned int _quadIndices[6] = {
			0,1,3,
			1,2,3
		};

		TypeSprite _type;

		void GenerateVAO();
		void BindVAO();
		void BindVBO(float* vertices, int AmmountOfVertices);
		void BindEBO(unsigned int* indices, int AmmountOfIndices);
		void UnbindBuffers();
		void DeleteBuffer();
	public:
		Sprite(bool transparency, Type type, Renderer* renderer, std::string name);
		Sprite(bool transparency, const char* path, Type type, Renderer* renderer, std::string name);
		Sprite(int width, int height, const char* path, bool transparency, Type type, Renderer* renderer, std::string name);
		~Sprite();
		void Init(Shader& shader);
		void LoadSprite();
		void LoadSprite(int width, int height);
		void LoadSprite(int width, int height, const char* path);
		void BindBuffers(float* quadVertex, float* triVertex, int quadVertexSize, int triVertexSize);
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
#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"sprite.h"

namespace Engine {
	Sprite::Sprite(bool transparency, Type type, Renderer* renderer, std::string name) {
		_transparency = transparency;
		_renderer = renderer;
		_texImporter = new TextureImporter();
	}

	Sprite::Sprite(bool transparency, const char* path, Type type, Renderer* renderer, std::string name) {
		_transparency = transparency;
		_renderer = renderer;
		_texImporter = new TextureImporter();
		_texImporter->SetPath(path);
	}

	Sprite::Sprite(int width, int height, const char* path, bool transparency, Type type, Renderer* renderer, std::string name) {
		_transparency = transparency;
		_renderer = renderer;
		_texImporter = new TextureImporter(width, height, path, transparency);
	}

	Sprite::~Sprite() {
		if (_texImporter != NULL) {
			delete _texImporter;
			_texImporter = NULL;
		}
	}

	void Sprite::GenerateVAO() {
		_renderer->GenerateVAO(_vao);
	}

	void Sprite::BindVAO() {
		_renderer->BindVAO(_vao);
	}

	void Sprite::BindVBO(float* vertices, int AmmountOfVertices) {
		_renderer->BindVBO(_vbo, vertices, AmmountOfVertices);
	}

	void Sprite::BindEBO(unsigned int* indices, int AmmountOfVertices) {
		_renderer->BindEBO(_ebo, indices, AmmountOfVertices);
	}

	void Sprite::Init(Shader& shader) {
		LoadSprite();
		_renderer->SetTexAttribPointer(shader.GetID());
		BindBuffers(texQuadVertices, texTriVertices, 36, 27);
	}

	void Sprite::LoadSprite() {
		if (_texImporter)
			_texImporter->LoadImage(_width, _height, _transparency);
		else
			std::cout << "Couldn't find image" << std::endl;
	}

	void Sprite::LoadSprite(int width, int height) {
		if (_texImporter)
			_texImporter->LoadImage(width, height, _transparency);
		else
			std::cout << "Couldn't find image" << std::endl;
	}

	void Sprite::LoadSprite(int width, int height, const char* path) {
		if (_texImporter) {
			_texImporter->SetPath(path);
			_texImporter->LoadImage(width, height, _transparency);
		}
		else
			std::cout << "Couldn't find image" << std::endl;
	}

	void Sprite::BindBuffers(float* quadVertex, float* triVertex, int quadVertexSize, int triVertexSize) {
		GenerateVAO();
		switch (_type)
		{
		case TypeSprite::quad:
			BindVBO(texQuadVertices, quadVertexSize);
			BindEBO(_quadIndices, 6);
			break;
		case TypeSprite::triangle:
			BindVBO(texTriVertices, triVertexSize);
			BindEBO(_triIndices, 3);
			break;
		default:
			break;
		}
	}

	void Sprite::BindTexture() {
		glBindTexture(GL_TEXTURE_2D, _texImporter->GetTexture());
		glActiveTexture(GL_TEXTURE0);
	}

	void Sprite::BlendSprite() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Sprite::UnBlendSprite() {
		glDisable(GL_BLEND);
	}

	void Sprite::DrawSprite(Shader& shader) {
		if (_transparency) {
			BlendSprite();
			BindTexture();
			switch (_type)
			{
			case TypeSprite::quad:
				_renderer->DrawSprite(shader, _vao, _vbo, texQuadVertices, 36, GetModel());
				break;

			case TypeSprite::triangle:
				_renderer->DrawSprite(shader, _vao, _vbo, texTriVertices, 27, GetModel());
				break;
			}
			UnBlendSprite();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			BindTexture();
			switch (_type)
			{
			case TypeSprite::quad:
				_renderer->DrawSprite(shader, _vao, _vbo, texQuadVertices, 36, GetModel());
				break;

			case TypeSprite::triangle:
				_renderer->DrawSprite(shader, _vao, _vbo, texTriVertices, 27, GetModel());
				break;
			}
			glDisable(GL_TEXTURE_2D);
		}
	}

	void Sprite::SetWidth(int width) {
		_width = width;
	}

	int Sprite::GetWidth() {
		return _width;
	}

	void Sprite::SetHeight(int height) {
		_height = height;
	}

	int Sprite::GetHeight() {
		return _height;
	}

	void Sprite::SetPath(const char* path) {
		if (_texImporter)
			_texImporter->SetPath(path);
		else
			std::cout << "Couldn't set path" << std::endl;
	}

	const char* Sprite::GetPath() {
		if (_texImporter)
			return _texImporter->GetPath();
		else
			return nullptr;
	}

	void Sprite::UnbindBuffers() {
		_renderer->UnbindBuffers();
	}

	void Sprite::DeleteBuffer() {
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	}
}


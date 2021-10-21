#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include"sprite.h"

namespace Engine {
	Sprite::Sprite(bool transparency, Renderer* renderer, Shader shader, std::string name) : Entity2D() {
		_transparency = transparency;
		_renderer = renderer;
		this->shader = shader;
		_texImporter = new TextureImporter();
	}

	Sprite::Sprite(bool transparency, const char* path, Renderer* renderer, Shader shader, std::string name) : Entity2D() {
		_transparency = transparency;
		_renderer = renderer;
		_texImporter = new TextureImporter();
		this->shader = shader;
		_texImporter->SetPath(path);
	}

	Sprite::Sprite(int width, int height, const char* path, bool transparency, Renderer* renderer, Shader shader, std::string name) : Entity2D() {
		_transparency = transparency;
		_renderer = renderer;
		this->shader = shader;
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

	void Sprite::Init() {
		LoadSprite();
		_renderer->SetTexAttribPointer(shader.GetID());
		BindBuffers();
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

	void Sprite::BindBuffers() {
		GenerateVAO();
		BindVAO();
		BindVBO(_vertices, 32);
		BindEBO(_quadIndices, 6);
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

	void Sprite::Color(float r, float g, float b){
		_vertices[3] = r;  _vertices[4] = g;  _vertices[5] = b;
		_vertices[11] = r; _vertices[12] = g; _vertices[13] = b;
		_vertices[19] = r; _vertices[20] = g; _vertices[21] = b;
		_vertices[27] = r; _vertices[28] = g; _vertices[29] = b;
	}

	void Sprite::Color(glm::vec3 color){
		   _vertices[3] = color.x;  _vertices[4] = color.y;  _vertices[5] = color.z;
		  _vertices[11] = color.x; _vertices[12] = color.y; _vertices[13] = color.z;
		  _vertices[19] = color.x; _vertices[20] = color.y; _vertices[21] = color.z;
		  _vertices[27] = color.x; _vertices[28] = color.y; _vertices[29] = color.z;
	}

	void Sprite::DrawSprite() {
		UpdateMatrices();
		if (_transparency) {
			BlendSprite();
			BindTexture();
			_renderer->DrawSprite(shader, _vao, _vbo, _vertices, 32, GetModel());
			UnBlendSprite();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			BindTexture();
			_renderer->DrawSprite(shader, _vao, _vbo, _vertices, 32, GetModel());
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

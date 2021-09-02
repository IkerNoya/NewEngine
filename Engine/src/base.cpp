#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "base.h"
using namespace Engine;

Base::Base(){
	_renderer = new Renderer();
	_window = new Window(800, 600);
}

Base::~Base() {
	if (_renderer != NULL) {
		delete _renderer;
		_renderer = NULL;
	}
	if (_renderer != NULL)
	{
		delete _window;
		_window = NULL;
	}
}

int Base::InitEngine(){
	_window->CreateWindow("Unreal Engine pero con Intellisense");

	if (!_renderer->InitializeGlew()) {
		return 0;
	}

	basicShader.Create("..//Engine//src//Shaders//vertex.shader", "..//Engine//src//Shaders//fragment.shader");

	unsigned int vao, vbo, ebo; //temporal hasta tener shape
	float* vertices = { 0 };
	unsigned int* indices = { 0 };
	_renderer->GenerateVAO(vao);
	_renderer->BindVAO(vao);
	_renderer->BindVBO(vbo, vertices, 18);
	_renderer->BindEBO(ebo, indices, 3);
	basicShader.SetVertexAttributes("position");
	basicShader.SetColorAttributes("color");

}

void Base::UpdateEngine(){
	while (!glfwWindowShouldClose(_window->GetWindow())){
		_renderer->BeginFrame(0.0f,0.0f,0.0f);
		Update();
		Draw();
		_renderer->EndFrame(_window->GetWindow());
	}
}

void Base::Draw() {
	unsigned int ebo, vbo, vao;
	float* vert = 0;
	_renderer->BindVAO(vao);
	_renderer->BindVBO(vbo, vert, 18);
	basicShader.SetVertexAttributes("position");
	basicShader.SetColorAttributes("color");
	basicShader.Use();
	_renderer->Draw();
	_renderer->UnbindBuffers();
}

void Base::UnloadEngine(){
	unsigned int vao, vbo, ebo; //temporal hasta tener shape
	_renderer->DeleteBuffers(vao, vbo, ebo);
}

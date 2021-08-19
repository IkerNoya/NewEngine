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

int Base::initEngine(){
	if (!_renderer->InitializeGlew()) {
		return 0;
	}
	_window->CreateWindow("Unreal Engine pero bueno");
}

void Base::updateEngine(){
	while (!glfwWindowShouldClose(_window->GetWindow())){
		_renderer->BeginFrame(1.0f,1.0f,1.0f);

		_renderer->EndFrame(_window->GetWindow());
	}
}

void Base::unloadEngine(){

}

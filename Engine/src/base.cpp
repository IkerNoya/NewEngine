#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "base.h"
using namespace Engine;

Base::Base(){
	_renderer = new Renderer();
}

Base::~Base(){
	if (_renderer != NULL) {
		delete _renderer;
		_renderer = NULL;
	}
}

int Base::InitEngine(){
	if (!_renderer->InitializeGlew()) {
		return 0;
	}

}

void Base::UpdateEngine(){
	while (!glfwWindowShouldClose(_window)){
		_renderer->BeginFrame(1.0f,1.0f,1.0f);

		_renderer->EndFrame(_window);
	}
}

void Base::UnloadEngine(){

}

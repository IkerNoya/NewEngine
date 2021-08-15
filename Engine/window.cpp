#include "window.h"
#include<iostream>

#include "GLFW/glfw3.h"
#include "GL/glew.h"

using namespace Engine;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window() {
	_window = NULL;
	_width = 800;
	_height = 600;
}

Window::Window(int width, int height) {
	_window = NULL;
	_width = width;
	_height = height;
}

Window::~Window() {

}

int Window::CreateWindow(const char* name) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(_width, _height, "NewEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

GLFWindow* Window::GetWindow() {
	return _window;
}

void Window::SetWidth(int width) {
	_width = width;
}

int Window::GetWidth() {
	return _width;
}

void Window::SetHeight(int height) {
	_height = height;
}

int Window::GetHeight() {
	return _height;
}
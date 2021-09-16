#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "renderer.h"
#include "shader.h"

#include <iostream>

using namespace Engine;

Renderer::Renderer() {
}

Renderer::~Renderer() {

}

bool Renderer::InitializeGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
	if (glewInit() != GLEW_OK) {
		std::cout << "Error in GLEW INIT" << std::endl;
		std::cout << glewGetErrorString(glewInit()) << std::endl;
		return false;
	}
	return true;
}

void Renderer::BeginFrame(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::EndFrame(GLFWwindow* window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
void Renderer::GenerateVAO(unsigned int& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}
void Renderer::BindVAO(unsigned int& vao) {
	glBindVertexArray(vao);
}
void Renderer::BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}
void Renderer::UnbindBuffers() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Renderer::Draw(Shader& shader, glm::mat4 model, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount){
	BindVAO(vao);
	BindVBO(vbo, vertices, verticesAmount);
	shader.SetVertexAttributes("position");
	shader.SetColorAttributes("color");
	shader.Use(model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}

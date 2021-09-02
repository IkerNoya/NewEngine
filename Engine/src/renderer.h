#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"
#include "shader.h"

//forward declaration of GLFWwindow
struct GLFWwindow;

namespace Engine {
	class ENGINE_API Renderer {
	public:
		Renderer();
		~Renderer();

		bool InitializeGlew();
		void BeginFrame(float r, float g, float b);
		void EndFrame(GLFWwindow* window);
		void GenerateVAO(unsigned int& vao);
		void BindVAO(unsigned int& vao);
		void BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount);
		void BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount);
		void UnbindBuffers();
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);
		void Draw(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount);
	};
}

#endif // !Renderer


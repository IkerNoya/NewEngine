#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"

//forward declaration of GLFWwindow
struct GLFWwindow;

namespace Engine {
	class ENGINE_API Renderer {
	private:
		float _vertices[18] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		unsigned int _indices[3] = {
			0,1,2
		};
		unsigned int VBO, VAO, EBO;
	public:
		Renderer();
		~Renderer();

		bool InitializeGlew();
		void BeginFrame(float r, float g, float b);
		void EndFrame(GLFWwindow* window);
		void GenerateVAO(unsigned int& vao);
		void GenerateVAO();
		void BindVAO(unsigned int& vao);
		void BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount);
		void BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount);
		void UnbindBuffers();
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);
		//void draw(Shader& shader, unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount);
		void Draw();
	};
}

#endif // !Renderer


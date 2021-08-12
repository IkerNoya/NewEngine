#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"

//forward declaration of GLFWwindow
class GLFWwindow;

namespace Engine {
	class ENGINE_API Renderer {
	private:
		
	public:
		Renderer();
		~Renderer();

		bool InitializeGlew();
		void SwapBuffers(GLFWwindow* window);

	};
}

#endif // !Renderer


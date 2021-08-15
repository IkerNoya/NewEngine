#ifndef BASE_H
#define BASE_H
#include "export.h"
#include "renderer.h"

GLFWwindow* Window;

namespace Engine {
	class ENGINE_API Base {
	private:
		Renderer* _renderer;
		GLFWwindow* _window;
	public:
		Base();
		~Base();

		int initEngine();
		void updateEngine();
		void unloadEngine();

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void unload() = 0;


	};
}

#endif // !BASE_H

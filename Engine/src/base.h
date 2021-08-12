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

		int InitEngine();
		void UpdateEngine();
		void UnloadEngine();

		virtual void init() = 0;
		virtual void Update() = 0;
		virtual void Unload() = 0;

	};
}

#endif // !BASE_H

#ifndef WINDOW_H
#define WINDOW_H
#include"src/export.h"
class GLFWindow;

namespace Engine {
	class ENGINE_API Window {
	private:
		GLFWindow* _window;
		int _width;
		int _height;
	public:
		Window();
		Window(int width, int height);
		~Window();
		int CreateWindow(const char* name);
		GLFWindow* GetWindow();
		void SetWidth(int width);
		int GetWidth();
		void SetHeight(int height);
		int GetHeight();
	};
}

#endif
#ifndef BASE_H
#define BASE_H

#include "export.h"
#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "shape.h"

namespace Engine {
	class ENGINE_API Base {
	protected:
		Renderer* _renderer;
		Window* _window;
		Shader basicShader;
	public:
		Base();
		~Base();

		int InitEngine();
		void UpdateEngine();
		void UnloadEngine();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Unload() = 0;
	};
}

#endif // !BASE_H

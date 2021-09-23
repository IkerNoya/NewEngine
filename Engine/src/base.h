#ifndef BASE_H
#define BASE_H

#include "export.h"
#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "shape.h"
#include "camera.h"

namespace Engine {
	class ENGINE_API Base {
	private:
		Renderer* _renderer;
		Window* _window;
	protected:
		Camera* _camera;
		Shader basicShader;
		Renderer* GetRenderer();
		Window* GetWindow();
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

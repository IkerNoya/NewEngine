#ifndef BASE_H
#define BASE_H

#include "export.h"
#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "shape.h"
#include "sprite.h"
#include "camera.h"
#include "input.h"

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
		Input input;
	public:
		Base();
		~Base();

		int Init();
		void Update();
		void Unload();

		virtual void InitGame() = 0;
		virtual void UpdateGame() = 0;
		virtual void UnloadGame() = 0;

	};
}

#endif // !BASE_H

#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "export.h"
#include "MyMath-Hernan/My.h"

namespace Engine {

	struct ENGINE_API Transform {
		My::Vector3 position;
		My::Quaternion rotation;
		My::Vector3 localScale;
	};

	class ENGINE_API Entity2D {
	private:
		My::Matrix4x4 model;
		My::Matrix4x4 translate;
		My::Matrix4x4 rotate;
		My::Matrix4x4 scale;
	protected:
		void UpdateModel();
	public:
		Transform transform;
		Entity2D();
		~Entity2D();
		void Rotate(float x, float y, float z);
		void Translate(float x, float y, float z);
		void Scale(float x, float y, float z);
		My::Matrix4x4 GetModel();
	};

}

#endif // !ENTITY2D_H


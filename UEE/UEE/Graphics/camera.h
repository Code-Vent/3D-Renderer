#ifndef UEE_CAMERA_H
#define UEE_CAMERA_H

#include"..\Physics\transform.h"
using uee::physx::Transform;
#include"../Math/matrix4x4.h"
using uee::math::Matrix4x4;
#include"../Math/vector3.h"
using uee::math::Vector3;

namespace uee
{
	namespace graphx
	{
		typedef struct Camera
		{
			Camera(const Vector3& pos, const Vector3& target, const Vector3& up);
			const float* GetViewMatrix();
			const float* GetProjectionMatrix(float w, float h);
			Matrix4x4 projectionM;
			Transform camTransform;
			void PanRight() {}
			void PanLeft() {}
			void ZoomIn() {}
			void ZoomOut() {}
			void Update();
		}camera;
	}
}
#endif
#ifndef UEE_TRANSFORM_H
#define UEE_TRANSFORM_H
#include<vector>
using std::vector;

#include"..\Math\vector3.h"
#include"..\Math\matrix4x4.h"
using uee::math::Vector3;
using uee::math::Matrix4x4;

namespace uee
{

	namespace physx
	{
		typedef struct Transform
		{
		private:
			Transform(const Matrix4x4& mat);
			Matrix4x4 modelM;
			static vector<Transform*> inputListeners;
		public:
			void Translate(const Vector3& trans);
			void TranslateGlobal(const Vector3& trans);
			void Rotate(const Vector3& euler);
			void Scale(const Vector3& scale);
			void PeekRight(float t = 0.5f);
			void PeekLeft(float t = 0.5f);
			void PeekUp(float t = 0.5f);
			void PeekDown(float t = 0.5f);
			void RotatePivoted(const Vector3& euler, const Vector3& pivot = Vector3::zero);
			void Orbit(const Vector3& euler, const Vector3& target = Vector3::zero);
			void GetForward(Vector3& forward);
			void GetUp(Vector3& up);
			void GetRight(Vector3& right);
			void GetPosition(Vector3& position);
			void GetOrientation(Quaternion& orient);
			void GetScale(Vector3& scale);
			static Transform Look(const Vector3& pos, const Vector3& target, const Vector3& up);
			static Transform Rotation(const Vector3& euler);
			static Transform RotationPivoted(const Vector3& euler, const Vector3& pivot);
			static Transform RotationTranslation(const Vector3& euler, const Vector3& trans);
			static Transform ScaledRotationTranslation(const Vector3&scale, const Vector3& euler, const Vector3& trans);
			static Transform Translation(const Vector3& trans);
			static Transform TranslationRotation(const Vector3& trans, const Vector3& euler);
			static Transform ScaledTranslationRotation(const Vector3& scale, const Vector3& trans, const Vector3& euler);
			static Transform Scaled(const Vector3& scale);
			static Transform ScaledPivoted(const Vector3& scale, const Vector3& pivot);
			static Transform ScaledRotation(const Vector3& scale, const Vector3& euler);
			static Transform ScaledTranslation(const Vector3& scale, const Vector3& trans);
			static Transform ScaledRotationPivoted(const Vector3& scale, const Vector3& euler, const Vector3& pivot);
			static void AddInputListener(Transform& listener);
			const Matrix4x4& GetModelMatrix()
			{
				return modelM;
			}
			static void KeyboardFunc(unsigned char key, int x, int y);
			void MoveRight(float X);
			void MoveForward(float Z);
			void MoveUp(float Y);
			void Pitch(float a);
			void Roll(float a);
			void Yaw(float a);
			friend Transform operator+(const Transform&, const Transform&);
			friend Transform operator*(const Transform&, const Transform&);

		}Transform;
	}
}
#endif

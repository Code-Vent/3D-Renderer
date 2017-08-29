#ifndef UEE_VECTOR_3_H
#define UEE_VECTOR_3_H
#include"vector4.h"
//using uee::math::vec4;
#include<iostream>
#include<string>
using namespace std;

namespace uee
{
	namespace math
	{
		typedef struct Vector3
		{
		private:
			union {
				struct
				{
					float x, y, z;
				};
				float xyz[3];
			};
		public:
			Vector3();
			Vector3(float x, float y, float z);
			Vector3(const Vector4&);
			float operator[](int i)const;
			float& operator[](int i);
			operator Vector4() { return Vector4(x, y, z, 0); }
			operator string();
			const Vector3& Normalize();
			void operator +=(const Vector3&);
			void operator -=(const Vector3&);
			operator const float*()const
			{
				return &x;
			}
			static float Angle(const Vector3& v1, const Vector3& v2);
			static float Magnitude(const Vector3& vector);
			static float SqrMagnitude(const Vector3& vector);
			static Vector3 Normalized(const Vector3& vector);
			static float Dot(const Vector3& a, const Vector3& b);
			static Vector3 Cross(const Vector3& a, const Vector3& b);
			static void OrthoNormalize(Vector3& normal, Vector3& tangent);
			static void OrthoNormalize(Vector3& normal, Vector3& tangent, Vector3& binormal);
			static Vector3 Project(const Vector3& vector, Vector3& onNormal, bool normalized = false);
			static float SqrDistance(const Vector3& a, const Vector3& b);
			static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
			static Vector3 Slerp(Vector3& a, Vector3& b, float t, bool normalized = false);
			static Vector3 Nlerp(const Vector3& a, const Vector3& b, float t);
			static Vector3 Reflect(const Vector3& inDirection, Vector3& inNormal, bool normalized = false);
			static const Vector3 one;
			static const Vector3 zero;
			static const Vector3 forward;
			static const Vector3 back;
			static const Vector3 up;
			static const Vector3 down;
			static const Vector3 right;
			static const Vector3 left;

			friend Vector3 operator+(const Vector3& a, const Vector3& b);
			friend Vector3 operator-(const Vector3& a, const Vector3& b);
			friend Vector3 operator*(const Vector3& a, const Vector3& b);
			friend Vector3 operator*(float a, const Vector3& b);
			friend Vector3 operator/(const Vector3& b, float a);
			friend Vector3 operator/(const Vector3& b, const Vector3& a);
			friend bool operator==(const Vector3& a, const Vector3& b);
			friend ostream& operator<<(ostream& os, const Vector3&);
		}vec3;

	}
}

#endif
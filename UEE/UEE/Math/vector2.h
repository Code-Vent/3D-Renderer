#ifndef UEE_VECTOR_2_H
#define UEE_VECTOR_2_H

#include<iostream>
using namespace std;

#include"vector3.h"
#include"vector4.h"

namespace uee
{
	namespace math
	{
		typedef struct Vector2
		{
		private:
			union {
				struct
				{
					float x, y;
				};
				float xy[2];
			};
		public:
			Vector2();
			Vector2(float x, float y);
			Vector2(const Vector3&);
			Vector2(const Vector4&);
			float operator[](int i)const;
			float& operator[](int i);
			operator Vector3() { Vector3(x, y, 0); }
			operator Vector4() { Vector4(x, y, 0, 0); }
			const Vector2& Normalize();
			void operator-=(const Vector2&);
			void operator+=(const Vector2&);
			operator const float*()const
			{
				return &x;
			}
			static float Magnitude(const Vector2& vector);
			static float SqrMagnitude(const Vector2& vector);
			static Vector2 Normalized(const Vector2& vector);
			static float Dot(const Vector2& a, const Vector2& b);
			static Vector2 Project(const Vector2& vector, Vector2& onNormal, bool normalized = false);
			static float SqrDistance(const Vector2& a, const Vector2& b);
			static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
			static Vector2 Slerp(Vector2& a, Vector2& b, float t, bool normalized = false);
			static Vector2 Reflect(const Vector2& inDirection, Vector2& inNormal, bool normalized = false);
			static const Vector2 one;
			static const Vector2 zero;
			static const Vector2 up;
			static const Vector2 down;
			static const Vector2 right;
			static const Vector2 left;

			friend Vector2 operator+(const Vector2& a, const Vector2& b);
			friend Vector2 operator-(const Vector2& a, const Vector2& b);
			friend Vector2 operator*(float a, const Vector2& b);
			friend Vector2 operator/(const Vector2& b, float a);
			friend bool operator==(const Vector2& a, const Vector2& b);
			friend ostream& operator<<(ostream& os, const Vector2&);
		}vec2;
	}
}
#endif
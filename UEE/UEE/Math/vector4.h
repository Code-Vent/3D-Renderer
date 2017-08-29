#ifndef UEE_VECTOR_4_H
#define UEE_VECTOR_4_H



#include<iostream>
using namespace std;

namespace uee
{
	namespace math
	{
		typedef struct Vector4
		{
		private:
			union
			{
				struct
				{
					float x, y, z, w;
				};
				float xyzw[4];
			};
		public:
			Vector4();
			Vector4(float x, float y, float z, float w);
			Vector4(const float xyz[], float w);
			const Vector4& Normalize();
			float operator[](int i)const;
			float& operator[](int i);
			void operator+=(const Vector4&);
			void operator-=(const Vector4&);
			operator const float*()const
			{
				return &x;
			}
			static float Magnitude(const Vector4& vector);
			static float SqrMagnitude(const Vector4& vector);
			static Vector4 Normalized(const Vector4& vector);
			static float Dot(const Vector4& a, const Vector4& b);
			static Vector4 Project(const Vector4& vector, Vector4& onNormal, bool normalized = false);
			static float SqrDistance(const Vector4& a, const Vector4& b);
			static Vector4 Lerp(const Vector4& a, const Vector4& b, float t);
			static Vector4 Slerp(Vector4& a, Vector4& b, float t, bool normalized = false);
			static Vector4 Nlerp(const Vector4& a, const Vector4& b, float t);
			static const Vector4 one;
			static const Vector4 zero;

			friend Vector4 operator+(const Vector4& a, const Vector4& b);
			friend Vector4 operator-(const Vector4& a, const Vector4& b);
			friend Vector4 operator*(const Vector4& a, const Vector4& b);
			friend Vector4 operator*(float a, const Vector4& b);
			friend Vector4 operator/(const Vector4& b, float a);
			friend bool operator==(const Vector4& a, const Vector4& b);
			friend ostream& operator<<(ostream& os, const Vector4&);
		}vec4;
	}
}
#endif
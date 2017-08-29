#include "vector4.h"
#include"mathf.h"
#include<stdlib.h>
#include<string.h>

#define USE_PRECISION SINGLE_PRECISION


namespace uee
{
	namespace math
	{

		const Vector4 Vector4::one = Vector4(1, 1, 1, 1);
		const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);

		Vector4::Vector4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		Vector4::Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4::Vector4(const float xyz[], float w)
		{
			x = xyz[0];
			y = xyz[1];
			z = xyz[2];
			w = w;
		}

		const Vector4 & Vector4::Normalize()
		{
			float mag = Magnitude(*this);

			if (mag == 0.0f)//For now
			{
				memset(xyzw, 0, sizeof(xyzw));
				return *this;
			}

			float oneOverMag = 1.0f / mag;
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
			w *= oneOverMag;

			return *this;
		}

		float Vector4::operator[](int i)const
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				return xyzw[i];
			default:
				return 0.0;
			}
		}

		float & Vector4::operator[](int i)
		{
			switch (i)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				return *(float*)0;
			}
		}

		void Vector4::operator+=(const Vector4 &v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}

		void Vector4::operator-=(const Vector4 &v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		}

		float Vector4::Magnitude(const Vector4 & v)
		{
			return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
		}

		float Vector4::SqrMagnitude(const Vector4 & v)
		{
			return (v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
		}

		Vector4 Vector4::Normalized(const Vector4 & v)
		{
			float mag = Magnitude(v);

			if (mag == 0.0f)//
			{
				return zero;
			}

			float oneOverMag = 1.0f / mag;
			return Vector4(v.x*oneOverMag, v.y*oneOverMag, v.z*oneOverMag, v.w*oneOverMag);
		}

		float Vector4::Dot(const Vector4 & a, const Vector4 & b)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
		}

		Vector4 Vector4::Project(const Vector4 & vector, Vector4 & onNormal, bool normalized)
		{
			if (!normalized)
			{
				onNormal.Normalize();
			}
			float mag = Dot(onNormal, vector);
			return mag * onNormal;
		}

		float Vector4::SqrDistance(const Vector4 & a, const Vector4 & b)
		{
			float x = b.x - a.x;
			float y = b.y - a.y;
			float z = b.z - a.z;
			float w = b.w - a.w;
			return x*x + y*y + z*z + w*w;
		}

		Vector4 Vector4::Lerp(const Vector4 & a, const Vector4 & b, float t)
		{
			t = Mathf::Clampf(t, 0, 1);
			return a + t*(b - a);
		}

		Vector4 Vector4::Slerp(Vector4 & a, Vector4 & b, float t, bool normalized)
		{
			if (!normalized)
			{
				a.Normalize();
				b.Normalize();
			}

			float dot = Vector4::Dot(a, b);
			dot = Mathf::Clampf(dot, -1, 1);
			float theta = Mathf::Acos(dot)*t;
			Vector4 relativeVec = (b - dot*a).Normalize();
			return Mathf::Cos(theta)*a + Mathf::Sin(theta)*relativeVec;
		}

		Vector4 Vector4::Nlerp(const Vector4 & a, const Vector4 & b, float t)
		{
			return Lerp(a, b, t).Normalize();
		}

		Vector4 operator+(const Vector4 & a, const Vector4 & b)
		{
			return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		}

		Vector4 operator-(const Vector4 & a, const Vector4 & b)
		{
			return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		}

		Vector4 operator*(const Vector4 & a, const Vector4 & b)
		{
			return Vector4(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w);
		}

		Vector4 operator*(float a, const Vector4 & b)
		{
			return Vector4(a*b.x, a*b.y, a*b.z, a*b.w);
		}

		Vector4 operator/(const Vector4 & b, float a)
		{
			return Vector4(b.x / a, b.y / a, b.z / a, b.w / a);
		}

		bool operator==(const Vector4 & a, const Vector4 & b)
		{
			return Mathf::IsFLTEqual(a.x, b.x, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.y, b.y, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.z, b.z, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.w, b.w, USE_PRECISION);
		}

		ostream & operator<<(ostream & os, const Vector4 & v)
		{
			os << "[" << v.x << " " << v.y << " " << v.z << " " << v.w << "]" << endl;
			return os;
		}

	}
}
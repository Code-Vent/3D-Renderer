#include "vector2.h"

#include<assert.h>
#include"mathf.h"
#include<stdlib.h>
#include<string.h>

#define USE_PRECISION SINGLE_PRECISION

namespace uee
{
	namespace math {

		const Vector2 Vector2::one = Vector2(1, 1);
		const Vector2 Vector2::zero = Vector2(0, 0);
		const Vector2 Vector2::up = Vector2(0, 1);
		const Vector2 Vector2::down = Vector2(0, -1);
		const Vector2 Vector2::right = Vector2(1, 0);
		const Vector2 Vector2::left = Vector2(-1, 0);

		Vector2::Vector2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		Vector2::Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2::Vector2(const Vector3 &v)
		{
			assert(v[2] != 0.0);
			x = v[0] / v[2];
			x = v[1] / v[2];
		}

		Vector2::Vector2(const Vector4 &v)
		{
			assert(v[2] != 0.0 && v[3] != 0.0);
			float r = v[2] / v[3];
			x = v[0] / v[3];
			y = v[1] / v[3];
			x /= r;
			y /= r;
		}

		float Vector2::operator[](int i)const
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				return xy[i];
			default:
				return 0.0;
			}
		}

		float & Vector2::operator[](int i)
		{
			switch (i)
			{
			case 0:
				return x;
			case 1:
				return y;
			default:
				return *(float*)0;
			}
		}

		const Vector2& Vector2::Normalize()
		{
			float mag = Magnitude(*this);

			if (mag < SINGLE_PRECISION)
			{
				memset(xy, 0, sizeof(xy));
				return *this;
			}

			float oneOverMag = 1.0f / mag;
			x *= oneOverMag;
			y *= oneOverMag;
			return *this;
		}

		void Vector2::operator-=(const Vector2 &v)
		{
			x -= v.x;
			y -= v.y;
		}

		void Vector2::operator+=(const Vector2 &v)
		{
			x += v.x;
			y += v.y;
		}

		float Vector2::Magnitude(const Vector2& v)
		{
			return sqrt(v.x*v.x + v.y*v.y);
		}

		float Vector2::SqrMagnitude(const Vector2& v)
		{
			return (v.x*v.x + v.y*v.y);
		}

		Vector2 Vector2::Normalized(const Vector2& v)
		{
			float mag = Magnitude(v);

			if (mag < SINGLE_PRECISION)
			{
				return zero;
			}

			float oneOverMag = 1.0f / mag;
			return Vector2(v.x*oneOverMag, v.y*oneOverMag);
		}

		float Vector2::Dot(const Vector2 & a, const Vector2 & b)
		{
			return a.x*b.x + a.y*b.y;
		}


		Vector2 Vector2::Project(const Vector2 & vector, Vector2 & onNormal, bool normalized)
		{

			if (!normalized)
			{
				onNormal.Normalize();
			}
			float mag = Dot(onNormal, vector);
			return mag * onNormal;
		}

		float Vector2::SqrDistance(const Vector2 & a, const Vector2 & b)
		{
			float x = b.x - a.x;
			float y = b.y - a.y;

			return x*x + y*y;
		}

		Vector2 Vector2::Lerp(const Vector2 & a, const Vector2 & b, float t)
		{
			t = Mathf::Clampf(t, 0, 1);
			return a + t*(b - a);
		}

		Vector2 Vector2::Slerp(Vector2 & a, Vector2 & b, float t, bool normalized)
		{
			if (!normalized)
			{
				a.Normalize();
				b.Normalize();
			}

			float dot = Vector2::Dot(a, b);
			dot = Mathf::Clampf(dot, -1, 1);
			float theta = Mathf::Acos(dot)*t;
			Vector2 relativeVec = (b - dot*a).Normalize();
			return Mathf::Cos(theta)*a + Mathf::Sin(theta)*relativeVec;
		}

		Vector2 Vector2::Reflect(const Vector2 & inDirection, Vector2 & inNormal, bool normalized)
		{
			if (!normalized)
				inNormal.Normalize();
			float m = Dot(inDirection, inNormal);
			return (inDirection - (2 * m)*inNormal);
		}

		Vector2 operator+(const Vector2 & a, const Vector2 & b)
		{
			return Vector2(a.x + b.x, a.y + b.y);
		}

		Vector2 operator-(const Vector2 & a, const Vector2 & b)
		{
			return Vector2(a.x - b.x, a.y - b.y);
		}

		Vector2 operator*(float a, const Vector2 & b)
		{
			return Vector2(a*b.x, a*b.y);
		}

		Vector2 operator/(const Vector2 & b, float a)
		{
			return Vector2(b.x / a, b.y / a);
		}

		bool operator==(const Vector2 & a, const Vector2 & b)
		{
			return Mathf::IsFLTEqual(a.x, b.x, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.y, b.y, USE_PRECISION);
		}

		ostream& operator<<(ostream& os, const Vector2 & v)
		{
			os << "[" << v.x << " " << v.y << "]" << endl;
			return os;
		}
	}
}
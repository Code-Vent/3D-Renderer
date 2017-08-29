#include "vector3.h"
#include"mathf.h"
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<iomanip>
#include<sstream>
using namespace std;

#define USE_PRECISION SINGLE_PRECISION


namespace uee
{
	namespace math {

		const Vector3 Vector3::one = Vector3(1, 1, 1);
		const Vector3 Vector3::zero = Vector3(0, 0, 0);
		const Vector3 Vector3::forward = Vector3(0, 0, 1);
		const Vector3 Vector3::back = Vector3(0, 0, -1);
		const Vector3 Vector3::up = Vector3(0, 1, 0);
		const Vector3 Vector3::down = Vector3(0, -1, 0);
		const Vector3 Vector3::right = Vector3(1, 0, 0);
		const Vector3 Vector3::left = Vector3(-1, 0, 0);

		Vector3::Vector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Vector3::Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3::Vector3(const Vector4 &v)
		{
			assert(v[3] != 0.0);
			x = v[0] / v[3];
			y = v[1] / v[3];
			z = v[2] / v[3];
		}

		float Vector3::operator[](int i)const
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				return xyz[i];
			default:
				return 0.0f;
			}
		}

		float & Vector3::operator[](int i)
		{
			switch (i)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				return *(float*)0;
			}
		}

		Vector3::operator string()
		{
			ostringstream ostr;
			ostr << setprecision(4) << " " << x << " " << y << " " << z;
			return ostr.str();
		}

		const Vector3& Vector3::Normalize()
		{
			float mag = Magnitude(*this);

			if (mag < SINGLE_PRECISION)
			{
				memset(xyz, 0, sizeof(xyz));
				return *this;
			}

			float oneOverMag = 1.0f / mag;
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;

			return *this;
		}

		void Vector3::operator+=(const Vector3 &v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void Vector3::operator-=(const Vector3 &v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		float Vector3::Angle(const Vector3 & v1, const Vector3 & v2)
		{
			float dot = Vector3::Dot(v1, v2);
			float squareMagV1V2 = Vector3::SqrMagnitude(v1)*Vector3::SqrMagnitude(v2);
			float cos = dot*Mathf::OneOverSqrt(squareMagV1V2);
			return Mathf::Acos(Mathf::Clampf(cos, -1, 1));
		}

		float Vector3::Magnitude(const Vector3& v)
		{
			return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		}

		float Vector3::SqrMagnitude(const Vector3& v)
		{
			return (v.x*v.x + v.y*v.y + v.z*v.z);
		}

		Vector3 Vector3::Normalized(const Vector3& v)
		{
			float mag = Magnitude(v);

			if (mag < SINGLE_PRECISION)
			{
				return zero;
			}

			float oneOverMag = 1.0f / mag;
			return Vector3(v.x*oneOverMag, v.y*oneOverMag, v.z*oneOverMag);
		}

		float Vector3::Dot(const Vector3 & a, const Vector3 & b)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z;
		}

		Vector3 Vector3::Cross(const Vector3 & a, const Vector3 & b)
		{
			return Vector3(
				a.y*b.z - a.z*b.y,
				a.z*b.x - a.x*b.z,
				a.x*b.y - a.y*b.x
				);
		}

		void Vector3::OrthoNormalize(Vector3 & normal, Vector3 & tangent)
		{
			Vector3 proj;
			normal.Normalize();
			proj = Project(tangent, normal, true);
			tangent -= proj;
			tangent.Normalize();
		}

		void Vector3::OrthoNormalize(Vector3 & normal, Vector3 & tangent, Vector3& binormal)
		{
			OrthoNormalize(normal, tangent);
			binormal = Cross(tangent, normal);
		}

		Vector3 Vector3::Project(const Vector3 & vector, Vector3 & onNormal, bool normalized)
		{
			if (!normalized)
			{
				onNormal.Normalize();
			}
			float mag = Dot(onNormal, vector);
			return mag * onNormal;
		}

		float Vector3::SqrDistance(const Vector3 & a, const Vector3 & b)
		{
			float x = b.x - a.x;
			float y = b.y - a.y;
			float z = b.z - a.z;

			return x*x + y*y + z*z;
		}

		Vector3 Vector3::Lerp(const Vector3 & a, const Vector3 & b, float t)
		{
			t = Mathf::Clampf(t, 0, 1);
			return a + t*(b - a);
		}

		Vector3 Vector3::Slerp(Vector3 & a, Vector3 & b, float t, bool normalized)
		{
			if (!normalized)
			{
				a.Normalize();
				b.Normalize();
			}

			float dot = Vector3::Dot(a, b);
			dot = Mathf::Clampf(dot, -1, 1);
			float theta = Mathf::Acos(dot)*t;
			Vector3 relativeVec = (b - dot*a).Normalize();
			return Mathf::Cos(theta)*a + Mathf::Sin(theta)*relativeVec;
		}

		Vector3 Vector3::Nlerp(const Vector3 & a, const Vector3 & b, float t)
		{
			return Lerp(a, b, t).Normalize();
		}

		Vector3 Vector3::Reflect(const Vector3 & inDirection, Vector3 & inNormal, bool normalized)
		{
			if (!normalized)
				inNormal.Normalize();
			float m = Dot(inDirection, inNormal);
			return (inDirection - (2 * m)*inNormal);
		}

		Vector3 operator+(const Vector3 & a, const Vector3 & b)
		{
			return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
		}

		Vector3 operator-(const Vector3 & a, const Vector3 & b)
		{
			return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
		}

		Vector3 operator*(const Vector3 & a, const Vector3 & b)
		{
			return Vector3(a.x*b.x, a.y*b.y, a.z*b.z);
		}

		Vector3 operator*(float a, const Vector3 & b)
		{
			return Vector3(a*b.x, a*b.y, a*b.z);
		}

		Vector3 operator/(const Vector3 & b, float a)
		{
			return Vector3(b.x / a, b.y / a, b.z / a);
		}

		Vector3 operator/(const Vector3 & rhs, const Vector3 & lhs)
		{
			return Vector3(rhs.x / lhs.x, rhs.y / lhs.y, rhs.z / lhs.z);
		}

		bool operator==(const Vector3 & a, const Vector3 & b)
		{
			return Mathf::IsFLTEqual(a.x, b.x, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.y, b.y, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.z, b.z, USE_PRECISION);
		}

		ostream& operator<<(ostream& os, const Vector3 & v)
		{
			os << "[" << v.x << " " << v.y << " " << v.z << "]" << endl;
			return os;
		}

	}
}
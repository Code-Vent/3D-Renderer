#include"quaternion.h"

#define USE_PRECISION SINGLE_PRECISION

using uee::math::Mathf;

namespace uee
{
	namespace math
	{
		const Quaternion Quaternion::identity = Quaternion(Vector3::zero, 1.0f);

		Quaternion::Quaternion()
		{
			xyz = vec3::zero;
			w = 0.0f;
		}

		Quaternion::Quaternion(float x, float y, float z, float w)
		{
			xyzw[0] = x;
			xyzw[1] = y;
			xyzw[2] = z;
			xyzw[3] = w;
			Normalize();
		}

		Quaternion::Quaternion(const vec3 &unitVec, float rad)
		{
			float angle = rad * 0.5f;
			xyz = sin(angle)*unitVec;
			w = cos(angle);
		}

		Quaternion::Quaternion(const Quaternion & q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
		}

		Quaternion::Quaternion(Quaternion && q) noexcept
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
		}

		Quaternion & Quaternion::operator=(Quaternion && q) noexcept
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
			return *this;
		}

		void Quaternion::operator+=(const Quaternion & q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			Normalize();
		}

		void Quaternion::operator-=(const Quaternion & q)
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			Normalize();
		}

		void Quaternion::operator*=(const Quaternion & q)
		{
			Quaternion qu = *this * q;
			qu.Normalize();
			this->x = qu.x;
			this->y = qu.y;
			this->z = qu.z;
			this->w = qu.w;
		}

		float Quaternion::operator[](int i)const
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

		Vector3 Quaternion::EulerAngles() const
		{
			return vec3(Mathf::Atan2(2 * x*w + 2 * y*z, 1 - 2 * x*x - 2 * y*y),
				Mathf::Asin(2 * w*y - 2 * z*x),
				Mathf::Atan2(2 * z*w + 2 * x*y, 1 - 2 * y*y - 2 * z*z));
		}

		Quaternion Quaternion::Euler(float x, float y, float z)
		{
			Quaternion pitch = Quaternion(vec3::right, x);
			Quaternion yaw = Quaternion(vec3::up, y);
			Quaternion roll = Quaternion(vec3::forward, z);
			return yaw * pitch * roll;
		}

		Quaternion Quaternion::operator-() const
		{
			return Quaternion(-x, -y, -z, -w);
		}

		Quaternion operator+(const Quaternion & lhs, const Quaternion & rhs)
		{
			Quaternion res = Quaternion(lhs.x + rhs.x,
				lhs.y + rhs.y,
				lhs.z + rhs.z,
				lhs.w + rhs.w);
			res.Normalize();
			return res;
		}

		Quaternion operator-(const Quaternion & lhs, const Quaternion & rhs)
		{
			Quaternion res = Quaternion(lhs.x - rhs.x,
				lhs.y - rhs.y,
				lhs.z - rhs.z,
				lhs.w - rhs.w);
			res.Normalize();
			return res;
		}

		Quaternion operator*(const Quaternion & lhs, const Quaternion & rhs)
		{
			Quaternion res = Quaternion(
				(((lhs.w * rhs.x) + (lhs.x * rhs.w)) + (lhs.y * rhs.z)) - (lhs.z * rhs.y),
				(((lhs.w * rhs.y) + (lhs.y * rhs.w)) + (lhs.z * rhs.x)) - (lhs.x * rhs.z),
				(((lhs.w * rhs.z) + (lhs.z * rhs.w)) + (lhs.x * rhs.y)) - (lhs.y * rhs.x),
				(((lhs.w * rhs.w) - (lhs.x * rhs.x)) - (lhs.y * rhs.y)) - (lhs.z * rhs.z)
				);
			res.Normalize();
			return res;
		}

		ostream & operator<<(ostream &os, const Quaternion &q)
		{
			os << "q(vec" << q.xyz << "  arg[" << q.w << "]" << ")" << endl;
			return os;
		}

		bool operator==(const Quaternion & a, const Quaternion & b)
		{
			return Mathf::IsFLTEqual(a.x, b.x, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.y, b.y, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.z, b.z, USE_PRECISION)
				&& Mathf::IsFLTEqual(a.w, b.w, USE_PRECISION);
		}

		Quaternion Quaternion::AngleAxis(float degrees, const Vector3 & axis)
		{
			float angle = Mathf::ToRadians(degrees);
			vec3 d = axis;
			d.Normalize();
			Quaternion r = Quaternion(d, angle);
			return r;
		}

		Quaternion Quaternion::FromToRotation(const Vector3 & from, const Vector3 & to)
		{
			float cosHalfAngleX2, recipCosHalfAngleX2;
			cosHalfAngleX2 = sqrt((2.0f * (1.0f + Vector3::Dot(from, to))));
			recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
			Vector3 axis = (recipCosHalfAngleX2 * Vector3::Cross(from, to));
			Quaternion r = Quaternion(axis[0], axis[1], axis[2], cosHalfAngleX2 * 0.5f);
			return r;
		}

		Quaternion Quaternion::Inverse(const Quaternion & q)
		{
			Quaternion res;
			res.x = -q.x;
			res.y = -q.y;
			res.z = -q.z;
			res.w = q.w;
			return res;
		}

		Quaternion Quaternion::Lerp(const Quaternion & a, const Quaternion & b, float t)
		{
			t = Mathf::Clampf(t, 0, 1);
			return Quaternion(a.x + t*(b.x - a.x),
				a.y + t*(b.y - a.y),
				a.z + t*(b.z - a.z),
				a.w + t*(b.w - a.w));
		}

		Quaternion Quaternion::Slerp(const Quaternion & q1, const Quaternion & q2, float t)
		{
			t = Mathf::Clampf(t, 0, 1);
			float dot = Dot(q1, q2);
			Quaternion u = Quaternion(q2.x - dot*q2.x, q2.y - dot*q2.y, q2.z - dot*q2.z, q2.w - dot*q2.w);
			float angle = acos(dot);
			float c = cos(t * angle);
			float s = sin(t * angle);

			return Quaternion(c*q1.x + s*u.x, c*q1.y + s*u.y, c*q1.z + s*u.z, c*q1.w + s*u.w);
		}

		Quaternion Quaternion::Nlerp(const Quaternion & q1, const Quaternion & q2, float t)
		{
			return Lerp(q1, q2, t);
		}

		Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 up)
		{
			float fourBiggestSquaredMinus1, biggest;
			float x, y, z, w;
			int i;
			Vector3 right;
			Vector3::OrthoNormalize(forward, up, right);

#define m11 right[0]
#define m21 right[1]
#define m31 right[2]
#define m12 up[0]
#define m22 up[1]
#define m32 up[2]
#define m13 forward[0]
#define m23 forward[1]
#define m33 forward[2]

			float fourWSquaredMinus1 = m11 + m22 + m33;
			float fourXSquaredMinus1 = m11 - m22 - m33;
			float fourYSquaredMinus1 = m22 - m11 - m33;
			float fourZSquaredMinus1 = m33 - m11 - m22;

			fourBiggestSquaredMinus1 = Mathf::Max(fourWSquaredMinus1, fourXSquaredMinus1,
				fourYSquaredMinus1, fourZSquaredMinus1, &i);
			biggest = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
			float mul = 0.25f / biggest;

			switch (i)
			{
			case 1:
				w = biggest;
				x = (m32 - m23) * mul;
				y = (m13 - m31) * mul;
				z = (m21 - m12) * mul;
				break;
			case 2:
				x = biggest;
				w = (m32 - m23) * mul;
				y = (m21 + m12) * mul;
				z = (m13 + m31) * mul;
				break;
			case 3:
				y = biggest;
				w = (m13 - m31) * mul;
				x = (m21 + m12) * mul;
				z = (m32 + m23) * mul;
				break;
			case 4:
				z = biggest;
				w = (m21 - m12) * mul;
				x = (m13 + m31) * mul;
				y = (m32 + m23) * mul;
				break;
			}

#undef m11
#undef m21
#undef m31
#undef m12
#undef m22
#undef m32
#undef m13
#undef m23
#undef m33
			return Quaternion(x, y, z, w);
		}

		float Quaternion::Angle(const Quaternion & q1, const Quaternion & q2)
		{
			Quaternion inv = Quaternion::Inverse(q2);
			Quaternion res = q1 * inv;
			return Mathf::Acos(res.w) * 2.0f;
		}

		float Quaternion::Dot(const Quaternion & q1, const Quaternion & q2)
		{
			return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
		}

		Vector3 Quaternion::Rotate(const Quaternion & quat, const Vector3 & vec)
		{
			float tmpX, tmpY, tmpZ, tmpW;
			tmpX = (((quat.w * vec[0]) + (quat.y * vec[2])) - (quat.z * vec[1]));
			tmpY = (((quat.w * vec[1]) + (quat.z * vec[0])) - (quat.x * vec[2]));
			tmpZ = (((quat.w * vec[2]) + (quat.x * vec[1])) - (quat.y * vec[0]));
			tmpW = (((quat.x * vec[0]) + (quat.y * vec[1])) + (quat.z * vec[2]));
			return vec3(
				((((tmpW * quat.x) + (tmpX * quat.w)) - (tmpY * quat.z)) + (tmpZ * quat.y)),
				((((tmpW * quat.y) + (tmpY * quat.w)) - (tmpZ * quat.x)) + (tmpX * quat.z)),
				((((tmpW * quat.z) + (tmpZ * quat.w)) - (tmpX * quat.y)) + (tmpY * quat.x))
				);

		}

		void Quaternion::Normalize()
		{
			float sqrmag = x*x + y*y + z*z + w*w, mag;
			if (sqrmag < SINGLE_PRECISION) {
				memset(&xyzw[0], 0, sizeof(xyzw));
				return;
			}
			mag = sqrt(sqrmag);
			x /= mag;
			y /= mag;
			z /= mag;
			w /= mag;
		}
	}
}
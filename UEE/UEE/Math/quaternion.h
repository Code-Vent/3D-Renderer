#ifndef UEE_QUATERNION_H
#define UEE_QUATERNION_H
#include<iostream>
using namespace std;

#include"mathf.h"
using uee::math::Mathf;
#include"vector3.h"
using uee::math::Vector3;

namespace uee
{
	namespace math
	{
		typedef struct Quaternion
		{
		private:
			union
			{
				struct
				{
					vec3 xyz;
					float w;
				};
				struct
				{
					float x, y, z, w;
				};

				float xyzw[4];
			};

		public:
			Quaternion();
			Quaternion(float x, float y, float z, float w);
			Quaternion(const vec3& unitVec, float radians);
			Quaternion(const Quaternion& q);
			Quaternion(Quaternion&& q)noexcept;
			Quaternion& operator=(Quaternion&& q)noexcept;
			Quaternion operator-() const;
			void operator+=(const Quaternion& q);
			void operator-=(const Quaternion& q);
			void operator*=(const Quaternion& q);
			float operator[](int i)const;
			Vector3 EulerAngles() const;
			static Quaternion Euler(float x, float y, float z);
			inline static Quaternion EulerDegrees(float x, float y, float z)
			{
				return Euler(Mathf::ToRadians(x),
					Mathf::ToRadians(y),
					Mathf::ToRadians(z));
			}
			inline static Quaternion EulerDegrees(const Vector3& e)
			{
				return Euler(Mathf::ToRadians(e[0]),
					Mathf::ToRadians(e[1]),
					Mathf::ToRadians(e[2]));
			}
			static Quaternion AngleAxis(float degrees, const Vector3& axis);
			static Quaternion FromToRotation(const Vector3& from, const Vector3& to);
			static Quaternion Inverse(const Quaternion& q1);
			static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
			static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
			static Quaternion Nlerp(const Quaternion& q1, const Quaternion& q2, float t);
			static Quaternion LookRotation(Vector3 forward, Vector3 upwards = Vector3::up);
			static float Angle(const Quaternion& q1, const Quaternion& q2);
			static float Dot(const Quaternion& q1, const Quaternion& q2);
			static Vector3 Rotate(const Quaternion& q, const Vector3& v);

			static const Quaternion identity;

		private:
			void Normalize();
			friend Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
			friend Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs);
			friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
			friend ostream& operator<<(ostream&, const Quaternion&);
			friend bool operator==(const Quaternion& a, const Quaternion& b);
		}quat;

	}
}
#endif
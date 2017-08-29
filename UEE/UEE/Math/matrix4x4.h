#ifndef UEE_MATRIX_4_4_H
#define UEE_MATRIX_4_4_H

#include<iostream>
using namespace std;

#include"vector3.h"
using uee::math::Vector3;
#include"vector4.h"
using uee::math::Vector4;
#include"quaternion.h"
using uee::math::Quaternion;

namespace uee
{
	namespace math
	{
		typedef struct Matrix4x4
		{
		private:
			union {
				struct
				{
					float m11, m21, m31, m41;
					float m12, m22, m32, m42;
					float m13, m23, m33, m43;
					float m14, m24, m34, m44;
				};
				vec4 cols[4];
				float elements[4 * 4];
			};

			mutable Matrix4x4 *inverse = nullptr;
			mutable Matrix4x4 *transpose = nullptr;
			float determinant()const;
			void clear();

		public:
			operator const float*()const
			{
				return &elements[0];
			}

			static const Matrix4x4 identity;

			Matrix4x4(const float elems[]);
			Matrix4x4(float val = 1.0f);
			Matrix4x4(const Vector3& vals);
			Matrix4x4(const Quaternion& q);

			~Matrix4x4() {
				if (inverse)
					delete inverse;
				if (transpose)
					delete transpose;
			}

			void GetColumn(int col, Vector4&)const;
			void GetRow(int row, Vector4&)const;
			void GetColumn(int col, Vector3&)const;
			void GetRow(int row, Vector3&)const;
			void SetColumn(int col, const Vector4&);
			void SetRow(int row, const Vector4&);
			void SetColumn(int col, const Vector3&);
			void SetRow(int row, const Vector3&);
			void SetT(const Vector3& trans);
			void SetR(const Quaternion& q);
			void SetS(const Vector3& scale);
			void SetTRS(const Vector3& trans, const Quaternion& q, const Vector3& scale);
			Vector3 MultiplyPoint(const Vector3& point)const;
			Vector3 MultiplyVector(const Vector3& vector)const;
			const Matrix4x4* Transpose() const;
			const Matrix4x4* Inverse() const;
			float Determinant() const;
			inline void operator*=(const Matrix4x4& rhs)
			{
				Matrix4x4 m = Multiply(*this, rhs);
				memcpy_s(elements, sizeof(elements), m.elements, sizeof(elements));
			}
			static Matrix4x4 LookAt(const Vector3& pos, const Vector3& target, const Vector3& up);
			static Matrix4x4 Ortho(float left, float right, float bottom, float top, float near, float far);
			static Matrix4x4 Perspective(float fov, float aspect, float near, float far);

			static Matrix4x4 R(const Vector3& euler);
			static Matrix4x4 RT(const Vector3& euler, const Vector3& trans);
			static Matrix4x4 TR(const Vector3& trans, const Vector3& euler);
			static Matrix4x4 STR(const Vector3& scale, const Vector3& trans, const Vector3& euler);
			static Matrix4x4 SRT(const Vector3& scale, const Vector3& euler, const Vector3& trans);
			static Matrix4x4 R0(const Vector3& euler, const Vector3& pivot);
			static Matrix4x4 T(const Vector3& trans);
			static Matrix4x4 S0(const Vector3& scale, const Vector3& pivot);
			static Matrix4x4 S(const Vector3& scale);
			static Matrix4x4 ST(const Vector3& scale, const Vector3& trans);
			static Matrix4x4 SR(const Vector3& scale, const Vector3& euler);
			static Matrix4x4 SR0(const Vector3& scale, const Vector3& euler, const Vector3& pivot);
			static Matrix4x4 L(const Vector3& pos, const Vector3& target, const Vector3& up);
			static Matrix4x4 L0(const Vector3& pos, const Vector3& target,
				const Vector3& up, const Vector3& pivot);

			static Matrix4x4 Multiply(const Matrix4x4&, const Matrix4x4&);
			friend ostream& operator<<(ostream&, const Matrix4x4&);
			inline friend Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);

		}mat4;
	}
}
#endif
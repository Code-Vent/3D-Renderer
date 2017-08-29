#include"matrix4x4.h"
#include<string.h>
#include<assert.h>

using uee::math::Mathf;

namespace uee {

	namespace math {

		const Matrix4x4 Matrix4x4::identity = Matrix4x4(1.0f);

		float Matrix4x4::determinant() const
		{
			//cout << "calculating determinant..." << endl;
			return (m11*(m22*m33 - m23*m32) + m12*(m23*m31 - m21*m33)
				+ m13*(m21*m32 - m22*m31));
		}

		void Matrix4x4::clear()
		{
			memset(elements, 0, sizeof(elements));
		}

		Matrix4x4::Matrix4x4(const float elems[])
		{
			memcpy_s(elements, sizeof(elements), elems, sizeof(elements));
		}

		Matrix4x4::Matrix4x4(float val)
		{
			clear();
			m11 = m22 = m33 = val;
			m44 = 1.0f;
		}

		Matrix4x4::Matrix4x4(const Vector3 & vals)
		{
			clear();
			m11 = vals[0];
			m22 = vals[1];
			m33 = vals[2];
			m44 = 1.0f;
		}

		Matrix4x4::Matrix4x4(const Quaternion & q)
		{
			clear();
			float w = q[3];
			float x = q[0];
			float y = q[1];
			float z = q[2];

			//0 column
			m11 = 1.0f - 2.0f*(y*y + z*z);
			m21 = 2.0f*(x*y + w*z);
			m31 = 2.0f*(x*z - w*y);

			//1 column
			m12 = 2.0f*(x*y - w*z);
			m22 = 1.0f - 2.0f*(x*x + z*z);
			m32 = 2.0f*(z*y + w*x);

			//2 column
			m13 = 2.0f*(x*z + w*y);
			m23 = 2.0f*(z*y - w*x);
			m33 = 1.0f - 2.0f*(x*x + y*y);

			m44 = 1.0f;
		}

		void Matrix4x4::GetColumn(int i, Vector4 &col)const
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				col[0] = cols[i][0];
				col[1] = cols[i][1];
				col[2] = cols[i][2];
				col[3] = cols[i][3];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::GetRow(int i, Vector4 &row)const
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				row[0] = elements[i + 0];
				row[1] = elements[i + 4];
				row[2] = elements[i + 8];
				row[3] = elements[i + 12];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::GetColumn(int i, Vector3 &col) const
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				col[0] = cols[i][0];
				col[1] = cols[i][1];
				col[2] = cols[i][2];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::GetRow(int i, Vector3 &row) const
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				row[0] = elements[i + 0];
				row[1] = elements[i + 4];
				row[2] = elements[i + 8];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::SetColumn(int i, const Vector4 &col)
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				cols[i][0] = col[0];
				cols[i][1] = col[1];
				cols[i][2] = col[2];
				cols[i][3] = col[3];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::SetRow(int i, const Vector4 & row)
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				elements[i + 0] = row[0];
				elements[i + 4] = row[1];
				elements[i + 8] = row[2];
				elements[i + 12] = row[3];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::SetColumn(int i, const Vector3 &col)
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				cols[i][0] = col[0];
				cols[i][1] = col[1];
				cols[i][2] = col[2];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::SetRow(int i, const Vector3 &row)
		{
			switch (i)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				elements[i + 0] = row[0];
				elements[i + 4] = row[1];
				elements[i + 8] = row[2];
				break;
			default:
				break;
			}
		}

		void Matrix4x4::SetT(const Vector3 & trans)
		{
			m14 = trans[0];
			m24 = trans[1];
			m34 = trans[2];
		}

		void Matrix4x4::SetR(const Quaternion& q)
		{
			float w = q[3];
			float x = q[0];
			float y = q[1];
			float z = q[2];

			//0 column
			m11 = 1.0f - 2.0f*(y*y + z*z);
			m21 = 2.0f*(x*y + w*z);
			m31 = 2.0f*(x*z - w*y);

			//1 column
			m12 = 2.0f*(x*y - w*z);
			m22 = 1.0f - 2.0f*(x*x + z*z);
			m32 = 2.0f*(z*y + w*x);

			//2 column
			m13 = 2.0f*(x*z + w*y);
			m23 = 2.0f*(z*y - w*x);
			m33 = 1.0f - 2.0f*(x*x + y*y);
		}

		void Matrix4x4::SetS(const Vector3 & scale)
		{
			m11 *= scale[0];
			m21 *= scale[0];
			m31 *= scale[0];

			m12 *= scale[1];
			m22 *= scale[1];
			m32 *= scale[1];

			m13 *= scale[2];
			m23 *= scale[2];
			m33 *= scale[2];
		}

		void Matrix4x4::SetTRS(const Vector3 & trans, const Quaternion& q, const Vector3 & scale)
		{
			SetR(q);
			SetS(scale);
			SetT(trans);
		}

		Vector3 Matrix4x4::MultiplyPoint(const Vector3 & point)const
		{
			float x, y, z;
			x = point[0] * m11 + point[1] * m12 + point[2] * m13 + m14;
			y = point[0] * m21 + point[1] * m22 + point[2] * m23 + m24;
			z = point[0] * m31 + point[1] * m32 + point[2] * m33 + m34;
			return Vector3(x, y, z);
		}

		Vector3 Matrix4x4::MultiplyVector(const Vector3 & vector)const
		{
			float x, y, z;
			x = vector[0] * m11 + vector[1] * m12 + vector[2] * m13;
			y = vector[0] * m21 + vector[1] * m22 + vector[2] * m23;
			z = vector[0] * m31 + vector[1] * m32 + vector[2] * m33;
			return Vector3(x, y, z);
		}

		const Matrix4x4 * Matrix4x4::Transpose() const
		{
			if (!transpose)
			{
				transpose = new Matrix4x4();
			}

			transpose->m11 = m11;	transpose->m12 = m21; transpose->m13 = m31;
			transpose->m21 = m12;	transpose->m22 = m22; transpose->m23 = m32;
			transpose->m31 = m13;	transpose->m32 = m23; transpose->m33 = m33;


			return transpose;
		}

		const Matrix4x4 * Matrix4x4::Inverse() const
		{
			if (!inverse)
			{
				inverse = new Matrix4x4();
			}

			float det = Determinant();
			//std::cout << "Determinat is " << det << std::endl;
			assert(fabs(det) > SINGLE_PRECISION);
			//std::cout << "Determinat is " << det << std::endl;
			float oneOverDet = 1.0f / det;

			inverse->m11 = (m22*m33 - m23*m32) * oneOverDet;
			inverse->m12 = (m13*m32 - m12*m33) * oneOverDet;
			inverse->m13 = (m12*m23 - m13*m22) * oneOverDet;
			inverse->m21 = (m23*m31 - m21*m33) * oneOverDet;
			inverse->m22 = (m11*m33 - m13*m31) * oneOverDet;
			inverse->m23 = (m13*m21 - m11*m23) * oneOverDet;
			inverse->m31 = (m21*m32 - m22*m31) * oneOverDet;
			inverse->m32 = (m12*m31 - m11*m32) * oneOverDet;
			inverse->m33 = (m11*m22 - m12*m21) * oneOverDet;

			// Compute the translation portion of the inverse
			inverse->m14 = -(m14*inverse->m11 + m24*inverse->m12 + m34*inverse->m13);
			inverse->m24 = -(m14*inverse->m21 + m24*inverse->m22 + m34*inverse->m23);
			inverse->m34 = -(m14*inverse->m31 + m24*inverse->m32 + m34*inverse->m33);


			return inverse;
		}

		float Matrix4x4::Determinant() const
		{
			static float det = determinant();
			return det;
		}

		Matrix4x4 Matrix4x4::LookAt(const Vector3 & pos, const Vector3 & target, const Vector3 & up)
		{
			Matrix4x4 m;
			Vector3 forward, upward, right;
			forward = pos - target;
			upward = up;
			Vector3::OrthoNormalize(forward, upward, right);
			//Row 1 is right
			m.m11 = right[0]; m.m12 = right[1]; m.m13 = right[2];
			//Row 2 is upward
			m.m21 = upward[0]; m.m22 = upward[1]; m.m23 = upward[2];
			//Row 3 is forward
			m.m31 = forward[0]; m.m32 = forward[1]; m.m33 = forward[2];

			m.m14 = -Vector3::Dot(right, pos);
			m.m24 = -Vector3::Dot(upward, pos);
			m.m34 = -Vector3::Dot(forward, pos);

			return m;
		}

		Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float near, float far)
		{
			Matrix4x4 m;
			m.m11 = 2.0f / (right - left);
			m.m22 = 2.0f / (top - bottom);
			m.m33 = 2.0f / (near - far);

			m.m14 = (left + right) / (left - right);
			m.m24 = (bottom + top) / (bottom - top);
			m.m34 = (near + far) / (near - far);
			return m;
		}

		Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float near, float far)
		{
			Matrix4x4 m;
			float oneOverTan = 1.0f / Mathf::Tan(Mathf::ToRadians(fov * 0.5f));
			m.m44 = 0.0f;
			m.m11 = oneOverTan / aspect;
			m.m22 = oneOverTan;
			m.m33 = (near + far) / (near - far);
			m.m34 = 2.0f*near*far / (near - far);
			m.m43 = -1.0f;
			return m;
		}

		Matrix4x4 Matrix4x4::R(const Vector3 & euler)
		{
			Quaternion q = Quaternion::EulerDegrees(euler);
			return Matrix4x4(q);
		}

		Matrix4x4 Matrix4x4::RT(const Vector3 & euler, const Vector3 & trans)
		{
			/*Matrix4x4 m = R(euler);
			m.m14 = trans[0];
			m.m24 = trans[1];
			m.m34 = trans[2];
			return m;*/
			return T(trans)*R(euler);
		}

		Matrix4x4 Matrix4x4::TR(const Vector3 & trans, const Vector3 & euler)
		{
			/*Matrix4x4 m = R(euler);
			m.m14 = m.m11*trans[0] + m.m12*trans[1] + m.m13*trans[2];
			m.m24 = m.m21*trans[0] + m.m22*trans[1] + m.m23*trans[2];
			m.m34 = m.m31*trans[0] + m.m32*trans[1] + m.m33*trans[2];
			return m;*/
			return R(euler)*T(trans);
		}

		Matrix4x4 Matrix4x4::STR(const Vector3 & scale, const Vector3 & trans, const Vector3 & euler)
		{
			return R(euler)*T(trans)*S(scale);
		}

		Matrix4x4 Matrix4x4::SRT(const Vector3 & scale, const Vector3 & euler, const Vector3 & trans)
		{
			return T(trans)*R(euler)*S(scale);
		}

		Matrix4x4 Matrix4x4::Multiply(const Matrix4x4 &lhs, const Matrix4x4 &rhs)
		{
			Matrix4x4 res;
			//Row 1
			res.m11 = lhs.m11*rhs.m11 + lhs.m12*rhs.m21 + lhs.m13*rhs.m31 + lhs.m14*rhs.m41;
			res.m12 = lhs.m11*rhs.m12 + lhs.m12*rhs.m22 + lhs.m13*rhs.m32 + lhs.m14*rhs.m42;
			res.m13 = lhs.m11*rhs.m13 + lhs.m12*rhs.m23 + lhs.m13*rhs.m33 + lhs.m14*rhs.m43;
			res.m14 = lhs.m11*rhs.m14 + lhs.m12*rhs.m24 + lhs.m13*rhs.m34 + lhs.m14*rhs.m44;

			//Row 2
			res.m21 = lhs.m21*rhs.m11 + lhs.m22*rhs.m21 + lhs.m23*rhs.m31 + lhs.m24*rhs.m41;
			res.m22 = lhs.m21*rhs.m12 + lhs.m22*rhs.m22 + lhs.m23*rhs.m32 + lhs.m24*rhs.m42;
			res.m23 = lhs.m21*rhs.m13 + lhs.m22*rhs.m23 + lhs.m23*rhs.m33 + lhs.m24*rhs.m43;
			res.m24 = lhs.m21*rhs.m14 + lhs.m22*rhs.m24 + lhs.m23*rhs.m34 + lhs.m24*rhs.m44;

			//Row 3
			res.m31 = lhs.m31*rhs.m11 + lhs.m32*rhs.m21 + lhs.m33*rhs.m31 + lhs.m34*rhs.m41;
			res.m32 = lhs.m31*rhs.m12 + lhs.m32*rhs.m22 + lhs.m33*rhs.m32 + lhs.m34*rhs.m42;
			res.m33 = lhs.m31*rhs.m13 + lhs.m32*rhs.m23 + lhs.m33*rhs.m33 + lhs.m34*rhs.m43;
			res.m34 = lhs.m31*rhs.m14 + lhs.m32*rhs.m24 + lhs.m33*rhs.m34 + lhs.m34*rhs.m44;

			//Row 4
			res.m41 = lhs.m41*rhs.m11 + lhs.m42*rhs.m21 + lhs.m43*rhs.m31 + lhs.m44*rhs.m41;
			res.m42 = lhs.m41*rhs.m12 + lhs.m42*rhs.m22 + lhs.m43*rhs.m32 + lhs.m44*rhs.m42;
			res.m43 = lhs.m41*rhs.m13 + lhs.m42*rhs.m23 + lhs.m43*rhs.m33 + lhs.m44*rhs.m43;
			res.m44 = lhs.m41*rhs.m14 + lhs.m42*rhs.m24 + lhs.m43*rhs.m34 + lhs.m44*rhs.m44;
			return res;
		}

		ostream & operator<<(ostream &os, const Matrix4x4 &m)
		{
			os << "| " << m.m11 << " " << m.m12 << " " << m.m13 << " " << m.m14 << " |" << endl;
			os << "| " << m.m21 << " " << m.m22 << " " << m.m23 << " " << m.m24 << " |" << endl;
			os << "| " << m.m31 << " " << m.m32 << " " << m.m33 << " " << m.m34 << " |" << endl;
			os << "| " << m.m41 << " " << m.m42 << " " << m.m43 << " " << m.m44 << " |" << endl;
			return os;
		}

		extern Matrix4x4 operator*(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
		{
			return Matrix4x4::Multiply(lhs, rhs);
		}

		Matrix4x4 Matrix4x4::R0(const Vector3 & euler, const Vector3 & pivot)
		{
			/*Matrix4x4 m = R(euler);

			m.m14 = -(m.m11*pivot[0] + m.m12*pivot[1] + m.m13*pivot[2]) + pivot[0];
			m.m24 = -(m.m21*pivot[0] + m.m22*pivot[1] + m.m23*pivot[2]) + pivot[1];
			m.m34 = -(m.m31*pivot[0] + m.m32*pivot[1] + m.m33*pivot[2]) + pivot[2];

			return m;*/
			return T(pivot) * R(euler) * T(-1 * pivot);
		}

		Matrix4x4 Matrix4x4::T(const Vector3 & trans)
		{
			Matrix4x4 m;
			m.m14 = trans[0];
			m.m24 = trans[1];
			m.m34 = trans[2];
			return m;
		}

		Matrix4x4 Matrix4x4::S0(const Vector3 & scale, const Vector3 & pivot)
		{
			return T(pivot)*S(scale)*T(-1 * pivot);
		}

		Matrix4x4 Matrix4x4::S(const Vector3 & scale)
		{
			return Matrix4x4(scale);
		}

		Matrix4x4 Matrix4x4::ST(const Vector3 & scale, const Vector3 & trans)
		{
			return T(trans)*S(scale);
		}

		Matrix4x4 Matrix4x4::SR(const Vector3 & scale, const Vector3 & euler)
		{
			return R(euler)*S(scale);
		}

		Matrix4x4 Matrix4x4::SR0(const Vector3 & scale, const Vector3 & euler, const Vector3 & pivot)
		{
			return T(pivot)*R(euler)*S(scale)*R(-1 * euler)*T(-1 * pivot);
		}

		Matrix4x4 Matrix4x4::L(const Vector3& pos, const Vector3& target, const Vector3& up)
		{
			Matrix4x4 m;
			Vector3 forward, upward, right;
			forward = pos - target;
			upward = up;
			Vector3::OrthoNormalize(forward, upward, right);

			m.m11 = right[0];
			m.m21 = right[1];
			m.m31 = right[2];
			m.m12 = up[0];
			m.m22 = up[1];
			m.m32 = up[2];
			m.m13 = forward[0];
			m.m23 = forward[1];
			m.m33 = forward[2];

			m.m14 = pos[0];
			m.m24 = pos[1];
			m.m34 = pos[2];
			return m;
		}

		Matrix4x4 Matrix4x4::L0(const Vector3 & pos, const Vector3 & target, const Vector3 & up, const Vector3 & pivot)
		{
			return T(pivot)*L(pos, target, up)*T(-1 * pivot);
		}

	}
}
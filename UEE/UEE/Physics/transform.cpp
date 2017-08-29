#include"transform.h"

#include"..\Math\vector4.h"
using uee::math::vec4;

#define X_SPEED 1.0f
#define Y_SPEED 1.0f
#define Z_SPEED 1.0f

#define X_ROT 5.0f
#define Y_ROT 5.0f
#define Z_ROT 5.0f

bool peekRight = false;
bool peekLeft = false;


float Horizontal = 0.0f;
float Vertical = 0.0f;
float Forward = 0.0f;

float HorizontalRot = 0.0f;
float VerticalRot = 0.0f;
float ForwardRot = 0.0f;

namespace uee
{
	namespace physx
	{
		vector<Transform*> Transform::inputListeners;


		Transform::Transform(const Matrix4x4& mat)
		{
			modelM = mat;
		}

		void Transform::Translate(const Vector3 & trans)
		{
			MoveRight(trans[0]);
			MoveUp(trans[1]);
			MoveForward(trans[2]);
		}

		void Transform::TranslateGlobal(const Vector3 & trans)
		{
			Vector3 pos;
			modelM.GetColumn(3, pos);
			modelM.SetColumn(3, Vector3(trans[0] + pos[0],
				trans[1] + pos[1],
				trans[2] + pos[2]));
		}

		void Transform::Rotate(const Vector3 & euler)
		{
			Roll(euler[2]);
			Pitch(euler[0]);
			Yaw(euler[1]);
		}

		void Transform::Scale(const Vector3 & scale)
		{
			Vector3 forward, up, right;
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			modelM.SetColumn(0, scale[0] * right);
			modelM.SetColumn(1, scale[1] * up);
			modelM.SetColumn(2, scale[2] * forward);
		}

		void Transform::PeekRight(float t)
		{
			Vector3 right, forward, up;
			t = Mathf::Clampf(t, 0, 1);
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			forward = Vector3::Nlerp(forward, right, t);
			right = Vector3::Cross(up, forward);
			modelM.SetColumn(0, right);
			modelM.SetColumn(2, forward);
		}

		void Transform::PeekLeft(float t)
		{
			Vector3 right, forward, up;
			t = Mathf::Clampf(t, 0, 1);
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			forward = Vector3::Nlerp(forward, -1 * right, t);
			right = Vector3::Cross(up, forward);
			modelM.SetColumn(0, right);
			modelM.SetColumn(2, forward);
		}

		void Transform::PeekUp(float t)
		{
			Vector3 right, forward, up;
			t = Mathf::Clampf(t, 0, 1);
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			forward = Vector3::Nlerp(forward, up, t);
			up = Vector3::Cross(forward, right);
			modelM.SetColumn(1, up);
			modelM.SetColumn(2, forward);
		}

		void Transform::PeekDown(float t)
		{
			Vector3 right, forward, up;
			t = Mathf::Clampf(t, 0, 1);
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			forward = Vector3::Nlerp(forward, -1 * up, t);
			up = Vector3::Cross(forward, right);
			modelM.SetColumn(1, up);
			modelM.SetColumn(2, forward);
		}

		void Transform::RotatePivoted(const Vector3 & euler, const Vector3& pivot)
		{
			Vector3 pos;
			Matrix4x4 m = Matrix4x4::R0(euler, pivot);
			modelM.GetColumn(3, pos);
			pos = m.MultiplyPoint(pos);
			modelM.SetColumn(3, pos);
		}

		void Transform::Orbit(const Vector3 & euler, const Vector3 & target)
		{
			Quaternion q = Quaternion::EulerDegrees(euler);
			Vector3 pos, up, forward, right;
			modelM.GetColumn(3, pos);
			modelM.GetColumn(1, up);
			forward = pos - target;
			pos = Quaternion::Rotate(q, forward) + target;
			Vector3::OrthoNormalize(forward, up, right);
			modelM.SetColumn(0, right);
			modelM.SetColumn(1, up);
			modelM.SetColumn(2, forward);
			modelM.SetColumn(3, pos);
		}

		void Transform::GetForward(Vector3 & forward)
		{
			modelM.GetColumn(2, forward);
		}

		void Transform::GetUp(Vector3 & up)
		{
			modelM.GetColumn(1, up);
		}

		void Transform::GetRight(Vector3 & right)
		{
			modelM.GetColumn(0, right);
		}

		void Transform::GetPosition(Vector3 & position)
		{
			modelM.GetColumn(3, position);
		}

		void Transform::GetOrientation(Quaternion & orient)
		{
			Vector3 forward, up;
			modelM.GetColumn(2, forward);
			modelM.GetColumn(1, up);
			orient = Quaternion::LookRotation(forward, up);
		}

		void Transform::GetScale(Vector3 & scale)
		{
			Vector3 forward, up, right;
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			scale[0] = Vector3::Magnitude(right);
			scale[1] = Vector3::Magnitude(up);
			scale[2] = Vector3::Magnitude(forward);
		}

		Transform Transform::Look(const Vector3 & pos, const Vector3 & target, const Vector3 & up)
		{
			return Transform(Matrix4x4::L(pos, target, up));
		}

		Transform Transform::Rotation(const Vector3 & euler)
		{
			return Transform(Matrix4x4::R(euler));
		}

		Transform Transform::RotationPivoted(const Vector3 & euler, const Vector3 & pivot)
		{
			return Transform(Matrix4x4::R0(euler, pivot));
		}

		Transform Transform::RotationTranslation(const Vector3 & euler, const Vector3 & trans)
		{
			return Transform(Matrix4x4::RT(euler, trans));
		}

		Transform Transform::ScaledRotationTranslation(const Vector3 & scale, const Vector3 & euler, const Vector3 & trans)
		{
			return Transform(Matrix4x4::SRT(scale, euler, trans));
		}

		Transform Transform::Translation(const Vector3 & trans)
		{
			return Transform(Matrix4x4::T(trans));
		}

		Transform Transform::TranslationRotation(const Vector3 & trans, const Vector3 & euler)
		{
			return Transform(Matrix4x4::TR(trans, euler));
		}

		Transform Transform::ScaledTranslationRotation(const Vector3 & scale, const Vector3 & trans, const Vector3 & euler)
		{
			return Transform(Matrix4x4::STR(scale, trans, euler));
		}

		Transform Transform::Scaled(const Vector3 & scale)
		{
			return Transform(Matrix4x4::S(scale));
		}

		Transform Transform::ScaledPivoted(const Vector3 & scale, const Vector3 & pivot)
		{
			return Transform(Matrix4x4::S0(scale, pivot));
		}

		Transform Transform::ScaledRotation(const Vector3 & scale, const Vector3 & euler)
		{
			return Transform(Matrix4x4::SR(scale, euler));
		}

		Transform Transform::ScaledTranslation(const Vector3 & scale, const Vector3 & trans)
		{
			return Transform(Matrix4x4::ST(scale, trans));
		}

		Transform Transform::ScaledRotationPivoted(const Vector3 & scale, const Vector3 & euler, const Vector3 & pivot)
		{
			return Transform(Matrix4x4::SR0(scale, euler, pivot));
		}

		void Transform::AddInputListener(Transform & listener)
		{
			inputListeners.push_back(&listener);
		}

		void Transform::KeyboardFunc(unsigned char key, int x, int y)
		{
			bool trans = false;
			bool rot = false;

			switch (key)
			{
			case 'r':
				cout << "Right" << endl;
				Horizontal = X_SPEED;
				trans = true;
				peekRight = true;
				break;
			case 'l':
				cout << "Left" << endl;
				Horizontal = -X_SPEED;
				trans = true;
				peekLeft = true;
				break;
			case 'u':
				cout << "Up" << endl;
				Vertical = Y_SPEED;
				trans = true;
				break;
			case 'd':
				cout << "Down" << endl;
				Vertical = -Y_SPEED;
				trans = true;
				break;
			case 'f':
				cout << "Forward" << endl;
				Forward = Z_SPEED;
				trans = true;
				break;
			case 'b':
				cout << "Back" << endl;
				Forward = -Z_SPEED;
				trans = true;
				break;
			case 'p':
				HorizontalRot = X_ROT;
				rot = true;
				break;
			case 'y':
				VerticalRot = Y_ROT;
				rot = true;
				break;
			case 'z':
				ForwardRot = Z_ROT;
				rot = true;
				break;
			default:
				break;
			}
			//cout << "Horizontal = " << Horizontal << endl;
			for each (Transform* t in inputListeners)
			{
				//if (peekLeft)
				//	t->PeekUp(0.2);
				//if (peekRight)
				//	t->PeekDown(0.2);
				t->Translate(Vector3(Horizontal, Vertical, Forward));
				if (rot)
					t->Orbit(Vector3(HorizontalRot, VerticalRot, ForwardRot), Vector3(0.0, 18.0, 0.0));
			}
			Horizontal = Vertical = Forward = 0.0f;
			HorizontalRot = VerticalRot = ForwardRot = 0.0f;
			peekRight = false;
			peekLeft = false;
		}

		void Transform::MoveRight(float d)
		{
			Vector3 right, pos;
			modelM.GetColumn(0, right);
			modelM.GetColumn(3, pos);
			modelM.SetColumn(3, Vector3(d*right[0] + pos[0],
				d*right[1] + pos[1],
				d*right[2] + pos[2]));
		}

		void Transform::MoveForward(float d)
		{
			Vector3 forward, pos;
			modelM.GetColumn(2, forward);
			modelM.GetColumn(3, pos);
			modelM.SetColumn(3, Vector3(d*forward[0] + pos[0],
				d*forward[1] + pos[1],
				d*forward[2] + pos[2]));
		}

		void Transform::MoveUp(float d)
		{
			Vector3 up, pos;
			modelM.GetColumn(1, up);
			modelM.GetColumn(3, pos);
			modelM.SetColumn(3, Vector3(d*up[0] + pos[0],
				d*up[1] + pos[1],
				d*up[2] + pos[2]));
		}

		void Transform::Pitch(float a)
		{
			Vector3 right;
			Vector3 forward;
			Vector3 up;
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			Quaternion q = Quaternion::AngleAxis(a, Vector3::right);
			right = Quaternion::Rotate(q, right);
			forward = Quaternion::Rotate(q, forward);
			up = Quaternion::Rotate(q, up);
			modelM.SetColumn(0, right);
			modelM.SetColumn(1, up);
			modelM.SetColumn(2, forward);
		}

		void Transform::Roll(float a)
		{
			Vector3 right;
			Vector3 forward;
			Vector3 up;
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			Quaternion q = Quaternion::AngleAxis(a, Vector3::forward);
			forward = Quaternion::Rotate(q, forward);
			right = Quaternion::Rotate(q, right);
			up = Quaternion::Rotate(q, up);
			modelM.SetColumn(1, up);
			modelM.SetColumn(0, right);
			modelM.SetColumn(2, forward);
		}

		void Transform::Yaw(float a)
		{
			Vector3 right;
			Vector3 forward;
			Vector3 up;
			modelM.GetColumn(0, right);
			modelM.GetColumn(1, up);
			modelM.GetColumn(2, forward);
			Quaternion q = Quaternion::AngleAxis(a, Vector3::up);
			up = Quaternion::Rotate(q, up);
			forward = Quaternion::Rotate(q, forward);
			right = Quaternion::Rotate(q, right);
			modelM.SetColumn(0, right);
			modelM.SetColumn(2, forward);
			modelM.SetColumn(1, up);
		}

		Transform operator+(const Transform &lhs, const Transform &rhs)
		{
			// TODO: insert return statement here
			return Transform(rhs.modelM * lhs.modelM);
		}

		Transform operator*(const Transform &lhs, const Transform &rhs)
		{
			// TODO: insert return statement here
			return Transform(lhs.modelM * rhs.modelM);
		}

	}
}
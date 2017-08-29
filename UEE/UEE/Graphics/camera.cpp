#include"camera.h"


#include"../../Dependencies/glew/glew.h"
#include"../../Dependencies/freeglut/freeglut.h"

namespace uee
{
	namespace graphx
	{
		Camera::Camera(const Vector3 & pos, const Vector3& target, const Vector3& up)
			:projectionM(Matrix4x4::identity),
			camTransform(Transform::Look(pos, target, up))

		{
			Transform::AddInputListener(camTransform);
		}

		const float * Camera::GetViewMatrix()
		{
			return *camTransform.GetModelMatrix().Inverse();
		}

		const float * Camera::GetProjectionMatrix(float w, float h)
		{
			float aspect = w / h;
			projectionM = Matrix4x4::Perspective(60.0f, aspect, 1.5, 700.0);
			return projectionM;
		}

		void Camera::Update()
		{
			//cout << "Update() called" << endl;
			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(*camTransform.GetModelMatrix().Inverse());
			glutPostRedisplay();
		}
	}
}
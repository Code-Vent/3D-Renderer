#include"model3D.h"
#include"..\..\Dependencies\glew\glew.h"
#include"..\..\Dependencies\freeglut\freeglut.h"
#include<stdio.h>
#include<assert.h>


namespace uee
{
	namespace entity
	{
		void Model3D::DrawMesh()
		{
			if (mesh_info == NULL)
				return;

			//glColor3f(0, 0, 1);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//glPolygonMode(GL_FRONT, GL_FILL);

			Render(irender);
			glFlush();
		}
	}
}
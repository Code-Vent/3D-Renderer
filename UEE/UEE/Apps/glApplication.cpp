#include"glApplication.h"

#include<stdio.h>

namespace uee
{
	namespace apps
	{
		GLApplication::GLApplication(GLUTInitParams* params)
		{
			Init(params);			
		}

		void GLApplication::Init(GLUTInitParams* params)
		{
			glutInit((int*)params->pargc, (char**)params->pargv);
			glutInitDisplayMode(params->displayMode);
			glutInitWindowSize(params->width, params->height);
			glutInitWindowPosition(params->x, params->y);
			glutInitContextVersion(params->contextVersionMajor,
				params->contextVersionMinor);
			glutInitContextProfile(params->contextProfile);

			glutCreateWindow(((char**)params->pargv)[0]);

			if (GLEW_OK != glewInit())
			{
				fprintf(stderr, "Unable to initialize GLEW ... exiting\n");
				exit(EXIT_FAILURE);
			}

			params->init();
			glutDisplayFunc(params->displayFunc);
			glutReshapeFunc(params->reshapeFunc);
			glutKeyboardFunc(params->keyboardFunc);

		}

		void GLApplication::Run()
		{
			glutMainLoop();
		}

		void GLApplication::Shutdown()
		{
		}
	}
}
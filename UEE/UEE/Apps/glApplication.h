#ifndef UEE_GLAPPLICATION_H
#define UEE_GLAPPLICATION_H

#include"application.h"

#include"..\..\Dependencies\glew\glew.h"
#include"..\..\Dependencies\freeglut\freeglut.h"

namespace uee
{
	namespace apps
	{
		struct GLUTInitParams
		{
			void* pargc;
			void* pargv;
			int width;
			int height;
			int x;
			int y;
			int contextVersionMajor;
			int contextVersionMinor;
			int contextProfile;
			unsigned displayMode;
			const char* windowName;
			void(*init) (void);
			void(*displayFunc) (void);
			void(*reshapeFunc) (int,int);
			void(*keyboardFunc) (unsigned char, int, int);
		};

		struct GLApplication : public Application
		{
			GLApplication(GLUTInitParams* params);
			virtual void Run();
			virtual void Shutdown();
		private:
			void Init(GLUTInitParams* params);
		};

	}
}

#endif
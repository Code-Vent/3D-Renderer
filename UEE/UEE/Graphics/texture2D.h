#ifndef UEE_TEXTURE_2D_H
#define UEE_TEXTURE_2D_H

#include<string>

using namespace std;

typedef unsigned char GLboolean;
typedef unsigned int GLenum;

namespace uee
{
	namespace graphx
	{
		typedef struct Texture2D
		{
			static Texture2D* Create(string dir, const char* filename,
				GLboolean compress = 0, GLboolean mipmap = 0);
			static void BindTexure(GLenum texUnit, Texture2D* tex = nullptr);
			static void DeleteTexure(Texture2D* tex);
		private:
			Texture2D();
			unsigned int texId;
			unsigned int format, type;
			int width, height;
		}sampler2D;

	}
}
#endif
#include"texture2D.h"
#include"..\Utils\utils.h"

using namespace uee::utils;

namespace uee
{
	namespace graphx
	{
		Texture2D::Texture2D()
		{
			texId = -1;
		}

		Texture2D * Texture2D::Create(string dir, const char * filename, GLboolean compressed
			, GLboolean mipmap)
		{
			Texture2D *tex = new Texture2D;
			BYTE* pixels;

			glGenTextures(1, &tex->texId);
			if (tex->texId == 0)
			{
				delete tex;
				return nullptr;
			}
			pixels = ReadImage((dir + "/" + filename).c_str(), &tex->format, &tex->type,
				&tex->width, &tex->height);
			if (pixels == nullptr)
			{
				delete tex;
				return nullptr;
			}
			glBindTexture(GL_TEXTURE_2D, tex->texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			if (!compressed)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width,
					tex->height, 0, tex->format, tex->type, pixels);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, tex->width,
					tex->height, 0, tex->format, tex->type, pixels);

			delete[] pixels;
			return tex;
		}

		void Texture2D::BindTexure(GLenum texUnit, Texture2D * tex)
		{
			if (tex == nullptr)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				return;
			}
			glActiveTexture(texUnit);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex->texId);
		}

		void Texture2D::DeleteTexure(Texture2D * tex)
		{
			glDeleteTextures(1, &tex->texId);
		}
	}
}
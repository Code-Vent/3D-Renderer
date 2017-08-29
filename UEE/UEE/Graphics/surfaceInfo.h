#ifndef UEE_SURFACE_INFO
#define UEE_SURFACE_INFO

#include"texture2D.h"

#include<stdio.h>
#include<string>

#include<stdlib.h>
#include<vector>

using namespace std;

typedef float color3[3];

namespace uee
{
	namespace graphx
	{
		typedef struct Surface_Info
		{
			Surface_Info()
				:id(++sid)
			{
			}

			const unsigned int id;//surface info id
			color3 ka;//material ambient property
			color3 kd;//material dissolve property
			color3 ks;//material specular property
			color3 ke;//material emmissive property
			float d = 1.0f;//dissolve
			float ns;//material shininess property
			float ni;//opacity_density , refractive index glass has refractive index 1.5
			unsigned short illum;//UEEuint16 illum;
			Texture2D* map_ka = nullptr;
			Texture2D* map_kd = nullptr;
			Texture2D* map_ks = nullptr;
			Texture2D* map_ke = nullptr;
			Texture2D* map_d = nullptr;
			Texture2D* map_bump = nullptr;
			Texture2D* map_ns = nullptr;
			Texture2D* map_ni = nullptr;
			Texture2D* bump = nullptr;
			unsigned int numOfUsers = 0;
		private:
			static unsigned int sid;
		}SURFACE_INFO;

		void LoadSurfaces(string dir, const char* filename);
		Surface_Info* GetSurface(const char* name);
	}
}
#endif
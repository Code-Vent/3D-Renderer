#ifndef UEE_FILE_UTILS_H
#define UEE_FILE_UTILS_H
#include"..\Core\core.h"

#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

#include"..\..\Dependencies\glew\glew.h"
#include"..\..\Dependencies\freeglut\freeglut.h"
#include"..\..\Dependencies\freeImage\FreeImage.h"
#include"..\..\Dependencies\freeImage\Utilities.h"


#include<vector>
using std::vector;
#include<string>
using std::string;

using namespace uee::core;

namespace uee {

	namespace utils
	{

		typedef struct face_group_info
		{
			char* name = UEE_NULL_PTR;
			char* material = UEE_NULL_PTR;
			UEEuint32 ibegin = 0;
			UEEuint32 iend = 0;
			UEEuint32 tris = 0;
			UEEuint32 quads = 0;
		}FGI;

		typedef struct new_mtl_info
		{
			char* name = UEE_NULL_PTR;
			char* ka = UEE_NULL_PTR;
			char* kd = UEE_NULL_PTR;
			char* ks = UEE_NULL_PTR;
			char* ke = UEE_NULL_PTR;
			char* ns = UEE_NULL_PTR;
			char* ni = UEE_NULL_PTR;
			char* d = UEE_NULL_PTR;
			char* illum = UEE_NULL_PTR;
			char* bump = UEE_NULL_PTR;
			char* map_ka = UEE_NULL_PTR;
			char* map_kd = UEE_NULL_PTR;
			char* map_ks = UEE_NULL_PTR;
			char* map_ke = UEE_NULL_PTR;
			char* map_ns = UEE_NULL_PTR;
			char* map_ni = UEE_NULL_PTR;
			char* map_bump = UEE_NULL_PTR;
			char* map_d = UEE_NULL_PTR;
		}NewMtl;

		//Returns path to .mtl file if material is present
		void ReadObjMeshFile(const char* path,
			char**file,
			char***verts,
			char***texCoords,
			char***normals,
			char***faces,
			char**mtllib,
			FGI***fg_info,
			vector<char*>& texs,
			vector<char*>& norms);

		void ReadObjMaterialLibFile(const char* path, char**file,
			NewMtl***newmtl);
		//void ReadShaderFile();
		//void ReadAudioFile();
		//void ReadAnimationFile();
		//void ReadImageFile();

		void WriteMeshXml(string dir, const char*meshname,
			char**verts,
			vector<char*> &texCoords,
			vector<char*> &normals,
			char**faces,
			FGI**fg_info,
			const char* mtlLib=nullptr);

		void WriteMaterialXml(const char* filepath, NewMtl**newmtl);
		char* ReadShaderFile(const char* filepath, char** p);
		BYTE* ReadImage(const char* path, GLenum* format,
			GLenum* type, int* width, int* height);
	}
}
#endif
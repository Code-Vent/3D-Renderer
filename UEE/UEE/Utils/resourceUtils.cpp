#include"resourceUtils.h"
#include"fileUtils.h"
#include"stringUtils.h"

#include<stdlib.h>
#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;



using namespace uee::utils;

namespace uee
{
	namespace utils
	{

		void AddMesh(string in_dir, const char * filename, string out_dir, const char *meshname, UEEresource_mode mode);
		void AddAnimation(string in_dir, const char * filename, string out_dir, const char *animname, UEEresource_mode mode);
		void AddAudio(string in_dir, const char * filename, string out_dir, const char *audioname, UEEresource_mode mode);
		void AddSprite(string in_dir, const char * filename, string out_dir, const char *spritename, UEEresource_mode mode);

		void AddResourceFromFile(const char* dir, const char* filename, UEEresource_types t,
			UEEresource_mode m)
		{
			char buf[128], *pstr;
			string cmd;
			string out_dir;

			strcpy_s(buf, filename);
			pstr = strstr(buf, ".");
			if (pstr)
				*pstr = 0;

			switch (t)
			{
			case UEE_MESH:
				out_dir = out_dir + "Resources\\Mesh\\" + buf;
				cmd = cmd + "mkdir " + out_dir;
				system(cmd.c_str());
				AddMesh(dir, filename, out_dir, buf, m);
				break;
			case UEE_AUDIO:
				break;
			case UEE_ANIMATION:
				break;
			case UEE_SPRITE:
				break;
			case UEE_UNKNOWN:
				break;
			default:
				break;
			}

		}

		void AddMesh(string in_dir, const char * filename, string out_dir, const char *meshname, UEEresource_mode mode)
		{
			int i = 0;
			char *objFile = 0,
				*matFile = 0,
				*matlib = 0,
				**verts = 0,
				**texCoords = 0,
				**normals = 0,
				**faces = 0,
				*pstr;
			FGI **faceGroups = 0;
			NewMtl** newmtl;
			string s, mtl, mtlpath;
			vector<char*> texs;
			vector<char*> norms;

			cout << "Adding a Mesh File" << endl;

			if (mode == UEEresource_mode::UEE_OBJ)
				ReadObjMeshFile(
					(in_dir + "/" + filename).c_str(),
					&objFile,
					&verts,
					&texCoords,
					&normals,
					&faces,
					&matlib,
					&faceGroups,
					texs,
					norms);
			else if (mode == UEEresource_mode::UEE_3DS)
			{

			}


			if (matlib)
			{
				ReadObjMaterialLibFile((in_dir + "/" + matlib).c_str(), &matFile, &newmtl);		
				mtl = mtl + meshname + ".surfaces.xml";
				WriteMaterialXml((out_dir + "/" + mtl).c_str(), newmtl);
				if (matFile)
					deleteCharArray(matFile);
				i = 0;
				while (newmtl[i])
				{
					if (isUsedPtr(newmtl[i])) {
						delete newmtl[i];
					}
					++i;
				}
				if (newmtl)
					deletePointerArray((void**)newmtl);

				WriteMeshXml(out_dir, meshname,
					verts,
					texs,
					norms,
					faces,
					faceGroups,
					mtl.c_str());
			}
			else
			{
				WriteMeshXml(out_dir, meshname,
					verts,
					texs,
					norms,
					faces,
					faceGroups);
			}

			if (objFile)
				deleteCharArray(objFile);
			if (verts)
				deletePointerArray((void**)verts);
			if (texCoords)
				deletePointerArray((void**)texCoords);;
			if (normals)
				deletePointerArray((void**)normals);
			if (faces)
				deletePointerArray((void**)faces);

			i = 0;
			while (faceGroups[i])
			{
				if (isUsedPtr(faceGroups[i])) {
					delete faceGroups[i];
				}
				++i;
			}
			if (faceGroups)
				deletePointerArray((void**)faceGroups);
		}

		void AddAnimation(string in_dir, const char * filename, string out_dir, const char *animname, UEEresource_mode mode)
		{
			cout << "Adding an Animation File" << endl;
		}

		void AddAudio(string in_dir, const char * filename, string out_dir, const char *audioname, UEEresource_mode mode)
		{
			cout << "Adding an Audio File" << endl;
		}

		void AddSprite(string in_dir, const char * filename, string out_dir, const char *spritename, UEEresource_mode mode)
		{
			cout << "Adding a Sprite File" << endl;
		}


	}

}


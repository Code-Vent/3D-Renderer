#pragma once
#include<stdio.h>
#include<string>
#include"surfaceInfo.h"

using namespace std;

namespace uee 
{
	namespace graphx
	{

		typedef struct Mesh_Info
		{
			struct Verts_Info
			{
				void* positions = nullptr;
				void* texCoords = nullptr;
				void* normals = nullptr;
				unsigned int total = 0;
				unsigned int format = 0;
			} verts_info;

			struct Group_Info
			{
				const char* name = nullptr;
				const Surface_Info* suface = nullptr;
				unsigned int size = 0;
				unsigned int ebo = -1;

				struct Tris
				{
					unsigned int total = 0;
					void* elems = nullptr;
				}tris;

				struct Quads
				{
					unsigned int total = 0;
					void* elems = nullptr;
				}quads;

				struct Group_Info* nextGroup = nullptr;

			}head;

			const char* name = nullptr;

		}Mesh_Info;


		bool
			ReadMeshInfo(string dir, const char* filename, Mesh_Info* m);

		void FreeMeshInfo(Mesh_Info* m);
		void FreeVertsInfo(Mesh_Info::Verts_Info* v);

		//TODO Add texture file path to Mesh_Info

	}
}
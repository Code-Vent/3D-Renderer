#include"fileUtils.h"
#include<vector>
#include<algorithm>
#include<assert.h>

using namespace std;


namespace uee {

	namespace utils
	{

		char* ReadCharsFile(const char* filepath);
		string ReadStringFile(const char* filepath);
		UEEuchar8* ReadBinaryFile(const char* filepath);
		efFace ReadFaceElement(char* f,
			UEEuint32* v,
			UEEuint32* t,
			UEEuint32* n);

		void ProcessObjMeshFaces(char** faces, char** verts,
			char** texCoords, char** normals, vector<char*>& texs, vector<char*>& norms);

		char* ReadCharsFile(const char* filepath)
		{
			FILE* file;
			fopen_s(&file, filepath, "rb");

			if (file == nullptr)
			{
				fprintf(stderr, "Could not open file \'%s\'", filepath);
				getchar();
				exit(EXIT_FAILURE);
			}

			fseek(file, 0, SEEK_END);
			UEEint32 length = ftell(file);
			fseek(file, 0, SEEK_SET);

			char* buffer = newCharArray(length);
			string fcontent(length, 0);

			fread(&fcontent[0], 1, length, file);
			fclose(file);

			auto it = remove_if(begin(fcontent), end(fcontent),
				[](char ch) { return ch == '\r'; });
			fcontent.erase(it, end(fcontent));

			memmove_s(buffer, length, fcontent.c_str(), length);
			return buffer;
		}

		string ReadStringFile(const char * filepath)
		{
			FILE* file;
			fopen_s(&file, filepath, "rb");

			if (file == nullptr)
			{
				fprintf(stderr, "Could not open file \'%s\'", filepath);
				getchar();
				exit(EXIT_FAILURE);
			}

			fseek(file, 0, SEEK_END);
			UEEint32 length = ftell(file);
			fseek(file, 0, SEEK_SET);

			string fcontent(length, 0);

			fread(&fcontent[0], 1, length, file);
			fclose(file);

			auto it = remove_if(begin(fcontent), end(fcontent),
				[](char ch) { return ch == '\r'; });
			fcontent.erase(it, end(fcontent));

			return fcontent;
		}

		UEEuchar8 * ReadBinaryFile(const char * filepath)
		{
			return nullptr;
		}

		efFace ReadFaceElement(char * f, UEEuint32 * v, UEEuint32 * t, UEEuint32 * n)
		{
			if (sscanf_s(f, "%u/%u/%u", v, t, n) == 3)
			{
				return efFace::UEE_VTN;
			}
			else if (sscanf_s(f, "%u//%u", v, n) == 2)
			{
				return efFace::UEE_VN;
			}
			else if (sscanf_s(f, "%u/%u", v, t) == 2)
			{
				return efFace::UEE_VT;
			}
			else if (sscanf_s(f, "%u", v) == 1)
			{
				return efFace::UEE_V;
			}
			else
			{
				return efFace::UEE_NONE;
			}
		}

		void
			ReadObjMeshFile(const char * path, char ** file,
				char *** verts, char *** texCoords, char *** normals,
				char *** faces, char**mtllib, FGI***faceGroups,
				vector<char*>& texs, vector<char*>& norms)
		{

			char *p, *ptr, *material = nullptr;
			char **ppVerts, **ppTexCoords, **ppNormals, **ppFaces;
			
			UEEuint32 i, numVerts = 0,
				numTexCoords = 0,
				numNormals = 0,
				numFaces = 0,
				numGroups = 0,
				faceIndex = 0;

			UEEbool flag = UEE_FALSE;
			struct face_group_info **ppGroups;

			*file = ReadCharsFile(path);
			ptr = *file;

			do
			{
				if (ptr[0] == 'v')
				{
					if (ptr[1] == ' ')
						++numVerts;
					else if (ptr[1] == 't')
						++numTexCoords;
					else if (ptr[1] == 'n')
						++numNormals;
				}
				else if (ptr[0] == 'f')
					++numFaces;
				else if (ptr[0] == 'g')
					++numGroups;
				else if (ptr[0] == 'm')
				{
					if (ptr[5] == 'b')
						*mtllib = ptr + 7;
				}
				ptr = strstr(ptr, "\n");

			} while (ptr++);

			if (numGroups == 0)
				numGroups = 1;

			*verts = (char**)newPointerArray(numVerts);
			*texCoords = (char**)newPointerArray(numTexCoords);
			*normals = (char**)newPointerArray(numNormals);
			*faces = (char**)newPointerArray(numFaces);
			*faceGroups = (FGI**)newPointerArray(numGroups + 1);

			ppVerts = *verts;
			ppTexCoords = *texCoords;
			ppNormals = *normals;
			ppFaces = *faces;
			ppGroups = *faceGroups;

			//printf("Number of Groups = %d\n", numGroups);

			if (numGroups == 1)
			{
				ppGroups[1] = new FGI;//(FGI*)newByteArray(sizeof(FGI));
				ppGroups[1]->ibegin = 0;
				ppGroups[1]->material = material;
				ppGroups[1]->name = "Default";
			}
			else
			{
				i = 1;
				while (ppGroups[i])
					ppGroups[i++] = new FGI;//(FGI*)newByteArray(sizeof(FGI));
			}

			ptr = *file;

			ptr = strtok_s(ptr, "\n", &p);

			while (ptr)
			{
				if (ptr[0] == 'v')
				{
					if (ptr[1] == ' ')
					{
						*ppVerts = ptr + 2;
						++ppVerts;
					}
					else if (ptr[1] == 't')
					{
						*ppTexCoords = ptr + 2;
						++ppTexCoords;
					}
					else if (ptr[1] == 'n')
					{
						*ppNormals = ptr + 2;
						++ppNormals;
					}
				}
				else if (ptr[0] == 'f')
				{
					*ppFaces = ptr;
					++ppFaces;
					++faceIndex;
				}
				else if (ptr[0] == 'g')
				{
					flag = UEE_TRUE;
					++ppGroups;
					(*ppGroups)->material = material;
					if (1 > strlen(ptr + 1))
						(*ppGroups)->name = ptr + 1;
					else
						(*ppGroups)->name = ptr + 2;
					(*ppGroups)->ibegin = faceIndex;
					if (isUsedPtr(ppGroups[-1])) {
						if (faceIndex != 0)
							ppGroups[-1]->iend = faceIndex;// -1;
					}
				}
				else if (ptr[0] == 'u')
				{
					if (ptr[1] == 's' && ptr[2] == 'e')
					{
						(*ppGroups)->material = ptr + 7;
						material = ptr + 7;
					}
				}

				ptr = strtok_s(NULL, "\n", &p);
			}

			if (flag)
				ppGroups[0]->iend = faceIndex;// -1;
			else
				ppGroups[1]->iend = faceIndex;// -1;

			ProcessObjMeshFaces(*faces, *verts, *texCoords, *normals, texs, norms);

			ppGroups = *faceGroups;
			ppFaces = *faces;
			i = 0;
			while (ppGroups[i])
			{
				if (isUsedPtr(ppGroups[i])) {
					printf("%s\n", ppGroups[i]->name);
					for (UEEuint32 j = ppGroups[i]->ibegin; j < ppGroups[i]->iend; ++j)
					{
						if (*ppFaces[j] == '3')
							ppGroups[i]->tris++;
						else
							ppGroups[i]->quads++;
					}
				}
				++i;
			}
			return;
		}

		void ReadObjMaterialLibFile(const char * path, char**file, NewMtl *** newmtl)
		{
			char *p, *ptr;
			UEEuint32 numMtl = 0, i;
			struct new_mtl_info **ppNewMtl;

			*file = ReadCharsFile(path);
			ptr = *file;

			do
			{
				if (ptr[0] == 'n') {
					if (ptr[1] == 'e')
						if (ptr[2] == 'w')
							if (ptr[5] == 'l')
								++numMtl;
				}
				ptr = strstr(ptr, "\n");

			} while (ptr++);

			*newmtl = (NewMtl**)newPointerArray(numMtl + 1);
			ppNewMtl = *newmtl;

			i = 1;
			while (ppNewMtl[i])
				ppNewMtl[i++] = new NewMtl;

			ptr = *file;
			ptr = strtok_s(ptr, "\n", &p);

			while (ptr)
			{
				if (ptr[0] == 'n') {
					if (ptr[1] == 'e')
						if (ptr[2] == 'w')
							if (ptr[5] == 'l')
							{
								++ppNewMtl;
								(*ppNewMtl)->name = ptr + 7;
							}
				}
				else if (ptr[0] == 'K' || ptr[0] == 'k')
				{
					if (ptr[1] == 'a')
						(*ppNewMtl)->ka = ptr + 3;
					else if(ptr[1] == 'd')
						(*ppNewMtl)->kd = ptr + 3;
					else if (ptr[1] == 's')
						(*ppNewMtl)->ks = ptr + 3;
					else if (ptr[1] == 'e')
						(*ppNewMtl)->ke = ptr + 3;
				}
				else if (ptr[0] == 'm' || ptr[0] == 'M')
				{
					if (ptr[4] == 'K')
					{
						if (ptr[5] == 'a')
							(*ppNewMtl)->map_ka = ptr + 7;
						else if (ptr[5] == 'd')
							(*ppNewMtl)->map_kd = ptr + 7;
						else if (ptr[5] == 's')
							(*ppNewMtl)->map_ks = ptr + 7;
						else if (ptr[5] == 'e')
							(*ppNewMtl)->map_ke = ptr + 7;
					}
					else if (ptr[4] == 'b')
					{
						(*ppNewMtl)->map_bump = ptr + 9;
					}
					else if (ptr[4] == 'd')
					{
						(*ppNewMtl)->map_d = ptr + 6;
					}
					else if (ptr[4] == 'n')
					{
						if (ptr[5] == 's')
							(*ppNewMtl)->map_ns = ptr + 7;
						else if(ptr[5] == 'i')
							(*ppNewMtl)->map_ni = ptr + 7;
					}
				}
				else if (ptr[0] == 'd')
				{
					(*ppNewMtl)->d = ptr + 2;
				}
				else if (ptr[0] == 'n' || ptr[0] == 'N')
				{
					if (ptr[1] == 's')
						(*ppNewMtl)->ns = ptr + 3;
					if (ptr[1] == 'i')
						(*ppNewMtl)->ni = ptr + 3;
				}
				else if (ptr[0] == 'i')
				{
					(*ppNewMtl)->illum = ptr + 6;
				}
				else if (ptr[0] == 'b')
				{
					if (ptr[3] == 'p')
						(*ppNewMtl)->bump = ptr + 5;
				}
				ptr = strtok_s(NULL, "\n", &p);
			}
		}

		void WriteMeshXml(string dir, const char * meshname, char ** verts,
			vector<char*> &texCoords, vector<char*> &normals, 
			char ** faces, FGI**faceGroups, const char* mtlLib)
		{
			char buf[16], *pbuf;
			float x, y, z, w;
			UEEbool tex, norm;
			UEEuint32 i = 0, totalVerts = 0, gsize, ebo = 0;
			FILE* file;
			vector<string> ebos;
			
			fopen_s(&file, (dir + "/" + meshname + ".mesh.xml").c_str(), "w");

			if (file == nullptr)
			{
				fprintf(stderr, "Could not Create file \'%s\'", meshname);
				getchar();
				exit(EXIT_FAILURE);
			}

			totalVerts = UsedPtrslen((void**)verts);
			tex = isUsedPtr(texCoords[totalVerts - 1]);
			norm = isUsedPtr(normals[totalVerts - 1]);

			pbuf = buf;
			sprintf_s(pbuf++, 16, "v");
			sprintf_s(pbuf++, 15, "%d", sscanf_s(verts[0], "%f%f%f%f", &x, &y, &z, &w));
			if (tex)
			{
				sprintf_s(pbuf++, 14, "t");
				sprintf_s(pbuf++, 13, "%d", sscanf_s(texCoords[totalVerts - 1], "%f%f%f%f", &x, &y, &z, &w));
			}
			if (norm)
			{
				sprintf_s(pbuf++, 12, "n");
				sprintf_s(pbuf++, 11, "%d", sscanf_s(normals[totalVerts - 1], "%f%f%f%f", &x, &y, &z, &w));
			}
			fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
			fprintf(file, "<Mesh ");
			fprintf(file, "name=\"%s\"", meshname);
			if (mtlLib)
			{
				//printf("Wow, You got some material\n");
				fprintf(file, " mtllib=\"%s\"", mtlLib);
			}
			fprintf(file, ">\n");
			{
				//Verts:
				fprintf(file, "<Verts ");
				fprintf(file, "total=\"%d\" ", totalVerts);
				fprintf(file, "format=\"%s\"", buf);
				fprintf(file, ">\n");
				{
					//V
					i = 0;
					while (verts[i])
					{
						fprintf(file, "<V ");
						if (isUsedPtr(texCoords[i]))
							fprintf(file, "t=\"%s\" ", texCoords[i]);
						if (isUsedPtr(normals[i]))
							fprintf(file, "n=\"%s\" ", normals[i]);
						fprintf(file, "> ");
						fprintf(file, "%s ", verts[i]);
						fprintf(file, "</V>\n");
						++i;
					}
					fprintf(file, "</Verts>\n");
				}
				{
					//Groups
					i = 0;
					while (faceGroups[i])
					{
						if (isUsedPtr(faceGroups[i]) &&
							(gsize = faceGroups[i]->iend - faceGroups[i]->ibegin) != 0)
						{
							fprintf(file, "<Group ");
							fprintf(file, "name=\"%s\" ", faceGroups[i]->name);
							fprintf(file, "material=\"%s\" ", faceGroups[i]->material);
							fprintf(file, "size=\"%d\" ", gsize);
							//ebo
							{
								auto it = find(begin(ebos), end(ebos), faceGroups[i]->material);
								if (it == end(ebos))
								{
									ebos.push_back(faceGroups[i]->material);
									fprintf(file, "ebo=\"%d\" ", ebo);
									ebo++;
								}
								else
								{
									fprintf(file, "ebo=\"%d\" ", (it - begin(ebos)));
								}

							}
							fprintf(file, ">\n");
							fprintf(file, "<Tris ");
							fprintf(file, "total=\"%d\"", faceGroups[i]->tris);
							fprintf(file, ">\n");
							for (UEEuint32 j = faceGroups[i]->ibegin; j < faceGroups[i]->iend; ++j)
							{
								if (*faces[j] == '3')
								{
									fprintf(file, "<F> ");
									fprintf(file, "%s ", faces[j] + 1);
									fprintf(file, "</F>\n");
								}
							}
							fprintf(file, "</Tris>\n");
							fprintf(file, "<Quads ");
							fprintf(file, "total=\"%d\"", faceGroups[i]->quads);
							fprintf(file, ">\n");
							for (UEEuint32 j = faceGroups[i]->ibegin; j < faceGroups[i]->iend; ++j)
							{
								if (*faces[j] == '4')
								{
									fprintf(file, "<F> ");
									fprintf(file, "%s ", faces[j] + 1);
									fprintf(file, "</F>\n");
								}
							}
							fprintf(file, "</Quads>\n");
							fprintf(file, "</Group>\n");
						}
						++i;
					}

				}
			}

			fprintf(file, "</Mesh>\n");

			fclose(file);
		}

		void WriteMaterialXml(const char *path, NewMtl ** newmtl)
		{
			UEEuint32 i = 0, totalMtls = 0;
			FILE* file;
			
			fopen_s(&file, path, "w");

			if (file == nullptr)
			{
				fprintf(stderr, "Could not Create file \'%s\'", path);
				getchar();
				exit(EXIT_FAILURE);
			}

			totalMtls = UsedPtrslen((void**)newmtl);
			fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
			fprintf(file, "<Surfaces ");
			fprintf(file, "total=\"%d\"", totalMtls);
			fprintf(file, ">\n");			

			while (newmtl[i])
			{
				if (isUsedPtr(newmtl[i]))
				{
						//Surface:
						fprintf(file, "<Surface ");
						{
							if (newmtl[i]->name)
								fprintf(file, "name=\"%s\"\n", newmtl[i]->name);
							if (newmtl[i]->ka && strlen(newmtl[i]->ka) > 1)
								fprintf(file, "ka=\"%s\"\n", newmtl[i]->ka);
							if (newmtl[i]->kd && strlen(newmtl[i]->kd) > 1)
								fprintf(file, "kd=\"%s\"\n", newmtl[i]->kd);
							if (newmtl[i]->ks && strlen(newmtl[i]->ks) > 1)
								fprintf(file, "ks=\"%s\"\n", newmtl[i]->ks);
							if (newmtl[i]->ke && strlen(newmtl[i]->ke) > 1)
								fprintf(file, "ke=\"%s\"\n", newmtl[i]->ke);
							if (newmtl[i]->ns && strlen(newmtl[i]->ns) > 0)
								fprintf(file, "ns=\"%s\"\n", newmtl[i]->ns);
							if (newmtl[i]->ni && strlen(newmtl[i]->ni) > 0)
								fprintf(file, "ni=\"%s\"\n", newmtl[i]->ni);
							if (newmtl[i]->d && strlen(newmtl[i]->d) > 0)
								fprintf(file, "d=\"%s\"\n", newmtl[i]->d);
							if (newmtl[i]->illum && strlen(newmtl[i]->illum) > 0)
								fprintf(file, "illum=\"%s\"\n", newmtl[i]->illum);
							if (newmtl[i]->map_ka && strlen(newmtl[i]->map_ka) > 1)
								fprintf(file, "map_ka=\"%s\"\n", newmtl[i]->map_ka);
							if (newmtl[i]->map_kd && strlen(newmtl[i]->map_kd) > 1)
								fprintf(file, "map_kd=\"%s\"\n", newmtl[i]->map_kd);
							if (newmtl[i]->map_ks && strlen(newmtl[i]->map_ks) > 1)
								fprintf(file, "map_ks=\"%s\"\n", newmtl[i]->map_ks);
							if (newmtl[i]->map_ke && strlen(newmtl[i]->map_ke) > 1)
								fprintf(file, "map_ke=\"%s\"\n", newmtl[i]->map_ke);
							if (newmtl[i]->map_ns && strlen(newmtl[i]->map_ns) > 1)
								fprintf(file, "map_ns=\"%s\"\n", newmtl[i]->map_ns);
							if (newmtl[i]->map_ni && strlen(newmtl[i]->map_ni) > 1)
								fprintf(file, "map_ni=\"%s\"\n", newmtl[i]->map_ni);
							if (newmtl[i]->map_bump && strlen(newmtl[i]->map_bump) > 1)
								fprintf(file, "map_bump=\"%s\"\n", newmtl[i]->map_bump);
							if (newmtl[i]->bump && strlen(newmtl[i]->bump) > 1)
								fprintf(file, "bump=\"%s\"\n", newmtl[i]->bump);
							if (newmtl[i]->map_d && strlen(newmtl[i]->map_d) > 1)
								fprintf(file, "map_d=\"%s\"\n", newmtl[i]->map_d);
						}
						fprintf(file, "/>\n");

				}
				++i;
			}

			fprintf(file, "</Surfaces>\n");

			fclose(file);
		}

		void ProcessObjMeshFaces(char** faces, char** verts,
			char** texCoords, char** normals, vector<char*>& texs, vector<char*>& norms)
		{
			UEEuint32 i = 0, j = 0, numVerts;
			char *f[4], *pchr;		

			numVerts = UsedPtrslen((void**)verts);

			texs.resize(numVerts);
			norms.resize(numVerts);

			while (faces[i])
			{
				UEEbool FaceIsQuad = UEE_TRUE;
				UEEuint32 v, t, n;
				efFace ef = efFace::UEE_NONE;

				f[0] = strstr(faces[i++], "f");
				f[1] = strstr(f[0] + 3, " ");
				f[2] = strstr(f[1] + 1, " ");
				f[3] = strstr(f[2] + 1, " ");

				{
					for (j = 0; j < 4; ++j)
					{
						efFace ef2;

						if (f[j] != NULL)
							ef2 = ReadFaceElement(f[j] + 1, &v, &t, &n);
						else {
							FaceIsQuad = UEE_FALSE;
							break;
						}

						if (j == 0)
							ef = ef2;
						switch (ef2)
						{
						case UEE_VTN:
							texs[v - 1] = texCoords[t - 1];
							norms[v - 1] = normals[n - 1];
							break;
						case UEE_VN:
							norms[v - 1] = normals[n - 1];
							texs[v - 1] = (char*)UEE_FREE_PTR;
							break;
						case UEE_VT:
							texs[v - 1] = texCoords[t - 1];
							norms[v - 1] = (char*)UEE_FREE_PTR;
							break;
						case UEE_V:
							break;
						case UEE_NONE:
							FaceIsQuad = UEE_FALSE;
							break;
						}
					}

					if (ef == efFace::UEE_V)
					{
						if (FaceIsQuad)
							*f[0] = '4';
						else
							*f[0] = '3';
					}
					else if (FaceIsQuad && ef != efFace::UEE_NONE)
					{
						pchr = strstr(f[3], "/");
						*pchr = '\0';
						pchr = strstr(f[2], "/");
						*pchr = ' ';
						strcpy_s(pchr + 1, strlen(pchr + 1), f[3]);
						pchr = strstr(f[1], "/");
						*pchr = ' ';
						strcpy_s(pchr + 1, strlen(pchr + 1), f[2]);
						pchr = strstr(f[0], "/");
						*pchr = ' ';
						strcpy_s(pchr + 1, strlen(pchr + 1), f[1]);
						*f[0] = '4';
					}
					else if (ef != efFace::UEE_NONE)
					{
						pchr = strstr(f[2], "/");
						*pchr = '\0';
						pchr = strstr(f[1], "/");
						*pchr = ' ';
						strcpy_s(pchr + 1, strlen(pchr + 1), f[2]);
						pchr = strstr(f[0], "/");
						*pchr = ' ';
						strcpy_s(pchr + 1, strlen(pchr + 1), f[1]);
						*f[0] = '3';
					}
				}
			}
		}


		static struct ImageLibManager
		{
			ImageLibManager()
			{
				FreeImage_Initialise(TRUE);
				FreeImage_SetOutputMessage(FreeImageErrorHandler);
			}

			~ImageLibManager()
			{
				FreeImage_DeInitialise();
			}

			const char* GetVersion()
			{
				return FreeImage_GetVersion();
			}

			static void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif,
				const char *message);
		}imageLibManager;

		FIBITMAP* GenericLoader(const char* lpszPathName, int flag);
		void GetPixelTypeAndFormat(FIBITMAP* bitmap, GLenum* type,
			GLenum* format);

		BYTE* ReadImage(const char* path, GLenum* format,
			GLenum* type, int* width, int* height)
		{
			BYTE* bits = nullptr;
			FIBITMAP* bitmap = GenericLoader(path, 0);
			if (!bitmap)
			{
				fprintf(stderr, "Could not read image file\n");
				return nullptr;
			}
			GetPixelTypeAndFormat(bitmap, type, format);
			*width = FreeImage_GetWidth(bitmap);
			*height = FreeImage_GetHeight(bitmap);
			unsigned bytes = *height * FreeImage_GetLine(bitmap);
			bits = new BYTE[bytes];
			memmove_s(bits, bytes, FreeImage_GetBits(bitmap), bytes);
			FreeImage_Unload(bitmap);
			return bits;
		}

		FIBITMAP* GenericLoader(const char* lpszPathName, int flag) {
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			fif = FreeImage_GetFileType(lpszPathName, 0);
			if (fif == FIF_UNKNOWN) {
				fif = FreeImage_GetFIFFromFilename(lpszPathName);
			}
			if ((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
				FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, flag);
				return dib;
			}
			return NULL;
		}

		void GetPixelTypeAndFormat(FIBITMAP* bitmap, GLenum* type,
			GLenum* format)
		{
			unsigned bpp;
			unsigned red_mask = FreeImage_GetRedMask(bitmap);
			unsigned green_mask = FreeImage_GetGreenMask(bitmap);
			unsigned blue_mask = FreeImage_GetBlueMask(bitmap);
			FREE_IMAGE_TYPE fit;
			BOOL res;
			res = FreeImage_HasPixels(bitmap);
			assert(res == TRUE);

			fit = FreeImage_GetImageType(bitmap);
			bpp = FreeImage_GetBPP(bitmap);

			switch (fit)
			{
			case FIT_UNKNOWN:
				break;
			case FIT_BITMAP:
				if (1 == bpp)
					*type = GL_BITMAP;
				else if (8 == bpp)
				{
					if ((red_mask == 0xE0) && (green_mask == 0x1C) && (blue_mask == 0x03))
					{
						*type = GL_UNSIGNED_BYTE_2_3_3_REV;
						*format = GL_RGB;
					}
					else if ((red_mask == 0x07) && (green_mask == 38) && (blue_mask == 0xC0))
					{
						*type = GL_UNSIGNED_BYTE_3_3_2;
						*format = GL_RGB;
					}
					else
					{
						*type = GL_UNSIGNED_BYTE;
						if (red_mask == 0xFF)
							*format = GL_RED;
						else if (blue_mask == 0xFF)
							*format = GL_BLUE;
						else if (green_mask == 0xFF)
							*format = GL_GREEN;
						else
							*format = GL_LUMINANCE;
					}
				}
				else if (16 == bpp)
				{
					*type = GL_UNSIGNED_SHORT;
					if ((red_mask == FI16_565_RED_MASK) && (green_mask == FI16_565_GREEN_MASK) &&
						(blue_mask == FI16_565_BLUE_MASK)) {
						// We are in RGB16 565 mode
						*type = GL_UNSIGNED_SHORT_5_6_5_REV;
						*format = GL_RGB;
					}
					else {
						// We are in RGB16 555 mode
						*type = GL_UNSIGNED_SHORT_1_5_5_5_REV;
						*format = GL_RGB;
					}
				}
				else if (24 == bpp)
				{
					*type = GL_UNSIGNED_BYTE;
					*format = GL_BGR;
				}
				else if (32 == bpp)
				{
					*type = GL_UNSIGNED_BYTE;
					*format = GL_BGRA;
				}
				break;
			case FIT_UINT16:
				*type = GL_UNSIGNED_SHORT;
				*format = GL_LUMINANCE;
				break;
			case FIT_INT16:
				*type = GL_SHORT;
				*format = GL_LUMINANCE;
				break;
			case FIT_UINT32:
				*type = GL_UNSIGNED_INT;
				*format = GL_LUMINANCE;
				break;
			case FIT_INT32:
				*type = GL_INT;
				*format = GL_LUMINANCE;
				break;
			case FIT_FLOAT:
				*type = GL_FLOAT;
				*format = GL_LUMINANCE;
				break;
			case FIT_DOUBLE:
				*type = GL_DOUBLE;
				*format = GL_LUMINANCE;
				break;
			case FIT_COMPLEX:
				*type = GL_DOUBLE;
				*format = GL_LUMINANCE;
				break;
			case FIT_RGB16:
				*type = GL_UNSIGNED_SHORT;
				*format = GL_RGB;
				break;
			case FIT_RGBA16:
				*type = GL_UNSIGNED_SHORT;
				*format = GL_RGBA;
				break;
			case FIT_RGBF:
				*type = GL_FLOAT;
				*format = GL_RGB;
				break;
			case FIT_RGBAF:
				*type = GL_FLOAT;
				*format = GL_RGBA;
				break;
			default:
				break;
			}
		}


		void ImageLibManager::FreeImageErrorHandler(FREE_IMAGE_FORMAT fif,
			const char *message)
		{
			printf("\n*** ");
			if (fif != FIF_UNKNOWN) {
				printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
			}
			printf(message);
			printf(" ***\n");
		}



		char* ReadShaderFile(const char* filepath, char** p)
		{
			*p = ReadCharsFile(filepath);
			char *s = strstr(*p, "$");
			if (s)
			{
				s[0] = '#';
				s[10] = ' ';
			}
			return s;
		}


	}

}
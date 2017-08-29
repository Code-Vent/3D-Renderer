#include"surfaceInfo.h"
#include"..\Utils\utils.h"
using namespace uee::utils;
#include<map>
using std::map;
#include<string>
using std::string;

namespace uee
{
	namespace graphx
	{
		unsigned int Surface_Info::sid = 0;
		void DeleteMaps(Surface_Info* s);

		struct SurfaceFactory
		{
			bool Exists(const char* name)
			{
				auto it = surfaces.find(name);
				return it != end(surfaces);
			}

			Surface_Info* AddSurface(const char* name)
			{
				Surface_Info* s = new Surface_Info();
				surfaces[name] = s;
				return s;
			}

			Surface_Info* GetSurface(const char* name)
			{
				Surface_Info* s = nullptr;
				if (Exists(name))
				{
					s = surfaces[name];
					s->numOfUsers++;
				}
				return s;//return the default surface instead
			}

			~SurfaceFactory()
			{
				for (auto it = begin(surfaces); it != end(surfaces); ++it)
				{
					DeleteMaps(it->second);
					delete it->second;
				}
			}
			map<string, Surface_Info*> surfaces;

		}surfaceFactory;

		void DeleteMaps(Surface_Info* s)
		{
			if (s->bump)
			{
				Texture2D::DeleteTexure(s->bump);
				delete s->bump;
			}
			if (s->map_bump)
			{
				Texture2D::DeleteTexure(s->map_bump);
				delete s->map_bump;
			}
			if (s->map_ka)
			{
				Texture2D::DeleteTexure(s->map_ka);
				delete s->map_ka;
			}
			if (s->map_kd)
			{
				Texture2D::DeleteTexure(s->map_kd);
				delete s->map_kd;
			}
			if (s->map_ks)
			{
				Texture2D::DeleteTexure(s->map_ks);
				delete s->map_ks;
			}
			if (s->map_ke)
			{
				Texture2D::DeleteTexure(s->map_ke);
				delete s->map_ke;
			}
			if (s->map_d)
			{
				Texture2D::DeleteTexure(s->map_d);
				delete s->map_d;
			}
			if (s->map_ns)
			{
				Texture2D::DeleteTexure(s->map_ns);
				delete s->map_ns;
			}
			if (s->map_ni)
			{
				Texture2D::DeleteTexure(s->map_ni);
				delete s->map_ni;
			}
		}

		void LoadSurfaces(string dir, const char* filename)
		{
			unsigned int totalSurfaces, i;
			FILE* file;
			char buf[256], *pbuf, *pbuf2;

			fopen_s(&file, (dir + "/" + filename).c_str(), "r");
			if (!file)
			{
				fprintf(stderr, "Could not open file %s\n", filename);
				exit(EXIT_FAILURE);
			}

			fgets(buf, sizeof(buf), file);//xml header
			fgets(buf, sizeof(buf), file);//<Surfaces total=
			sscanf_s(buf + 17, "%d", &totalSurfaces);

			//pbuf2 = strstr(pbuf + 8 + i, "m");
			//i = MakeString(pbuf2 + 8, &mtllib, "\"");

			while (totalSurfaces--)
			{
				fgets(buf, sizeof(buf), file);//<Surface name=
				pbuf = strstr(buf, "name");
				i = MakeString(pbuf + 6, &pbuf2, "\"");
				if (surfaceFactory.Exists(pbuf2))
				{
					do
					{
						fgets(buf, sizeof(buf), file);
					} while (buf[0] != '/');

				}
				else
				{
					Surface_Info* s = surfaceFactory.AddSurface(pbuf2);
					//printf("%s\n", pbuf2);
					do
					{
						fgets(buf, sizeof(buf), file);
						switch (buf[0])
						{
						case 'k':
							if (buf[1] == 'a')
								sscanf_s(&buf[4], "%f%f%f", &s->ka[0], &s->ka[1], &s->ka[2]);
							else if (buf[1] == 'd')
								sscanf_s(&buf[4], "%f%f%f", &s->kd[0], &s->kd[1], &s->kd[2]);
							else if (buf[1] == 's')
								sscanf_s(&buf[4], "%f%f%f", &s->ks[0], &s->ks[1], &s->ks[2]);
							else if (buf[1] == 'e')
								sscanf_s(&buf[4], "%f%f%f", &s->ke[0], &s->ke[1], &s->ke[2]);
							break;
						case 'n':
							if (buf[1] == 's')
								sscanf_s(&buf[4], "%f", &s->ns);
							if (buf[1] == 'i')
								sscanf_s(&buf[4], "%f", &s->ni);
							break;
						case 'd':
							sscanf_s(&buf[4], "%f", &s->d);
							break;
						case 'i':
							sscanf_s(&buf[4], "%hu", &s->illum);
							break;
						case 'b':
							//Load bump texture to get texMatrix
							//Texture::Load(texName, s->id);
							i = MakeString(&buf[6], &pbuf, "\"");
							s->bump = Texture2D::Create(dir,pbuf, 1);
							break;
						case 'm':
							if (buf[4] == 'k')
							{
								if (buf[5] == 'a')
								{
									//Load map_ka texture to get its texMatrix;
									i = MakeString(&buf[8], &pbuf, "\"");
									s->map_ka = Texture2D::Create(dir, pbuf, 1);
								}
								else if (buf[5] == 'd')
								{
									//Load map_kd texture to get its texMatrix;
									i = MakeString(&buf[8], &pbuf, "\"");
									s->map_kd = Texture2D::Create(dir, pbuf, 1);
								}
								else if (buf[5] == 's')
								{
									//Load map_ks texture to get its texMatrix;
									i = MakeString(&buf[8], &pbuf, "\"");
									s->map_ks = Texture2D::Create(dir, pbuf, 1);
								}
								else if (buf[5] == 'e')
								{
									//Load map_ke texture to get its texMatrix;
									i = MakeString(&buf[8], &pbuf, "\"");
									s->map_ke = Texture2D::Create(dir, pbuf, 1);
								}
							}
							else if (buf[4] == 'b')
							{
								//Load map_bump texture to get its texMatrix;
								i = MakeString(&buf[10], &pbuf, "\"");
								s->map_bump = Texture2D::Create(dir, pbuf, 1);
							}
							else if (buf[4] == 'n')
							{
								if (buf[5] == 's')
								{
									//Load map_ns texture to get its texMatrix;
									i = MakeString(&buf[8], &pbuf, "\"");
									s->map_ns = Texture2D::Create(dir, pbuf, 1);
								}
								else if (buf[5] == 'i')
								{
									//Load map_ni texture to get its texMatrix;
									i = MakeString(&buf[8], &pbuf, "\"");
									s->map_ni = Texture2D::Create(dir, pbuf, 1);
								}
							}
							else if (buf[4] == 'd')
							{
								//Load map_d texture to get its texMatrix;
								i = MakeString(&buf[7], &pbuf, "\"");
								s->map_d = Texture2D::Create(dir, pbuf, 1);
							}
							break;
						}
					} while (buf[0] != '/');
					//printf("ks = %f %f %f\n", s->ks[0], s->ks[1], s->ks[2]);
				}
			}
			fclose(file);
		}

		Surface_Info * GetSurface(const char * name)
		{
			return surfaceFactory.GetSurface(name);
		}
	}
}
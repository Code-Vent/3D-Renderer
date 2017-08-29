#include"meshInfo.h"

#include<stdlib.h>
#include<assert.h>
#include<string.h>
//#include"ram.h"
#include<iostream>
using std::cout;
using std::endl;

#include"../Utils/stringUtils.h"
using namespace uee::utils;

namespace uee {
	namespace graphx {

		bool
			ReadMeshInfo(string dir, const char* filename, Mesh_Info* m)
		{
			unsigned ebo;
			unsigned int i = 0, total = 0, *pu, u1, u2, u3, u4;
			Mesh_Info::Group_Info* pg;
			FILE* file;
			char buf[256], *pbuf, *pbuf2, *mtllib = nullptr, *material = nullptr;
			

			fopen_s(&file, (dir + "/" + filename).c_str(), "r");

			if (!file)
			{
				fprintf(stderr, "Could not open file %s\n", filename);
				exit(EXIT_FAILURE);
			}

			fgets(buf, sizeof(buf), file);//xml header
			fgets(buf, sizeof(buf), file);//<Mesh name=
			if (buf[1] != 'M')
				return false;
			pbuf = strstr(buf, "n");
			i = MakeString(pbuf + 6, (char**)&m->name, "\"");
			pbuf2 = strstr(pbuf + 8 + i, "m");

			if (pbuf2)
			{
				i = MakeString(pbuf2 + 8, &mtllib, "\"");
				//cout << mtllib << endl;
				LoadSurfaces(dir, mtllib);
			}

			fgets(buf, sizeof(buf), file);//<Verts
			if (buf[1] != 'V')
				return false;
			pbuf = strstr(buf, "to");//total=
			unsigned int totalVerts;
			sscanf_s(pbuf + 7, "%d", &totalVerts);
			m->verts_info.total = totalVerts;

			unsigned vx = 0, tx = 0, nx = 0;
			pbuf = strstr(buf, "f");//format=
			sscanf_s(pbuf + 9, "%d", &vx);

			if (*(pbuf + 10) == 't')
				sscanf_s(pbuf + 11, "%d", &tx);

			if (*(pbuf + 10) == 'n')
				sscanf_s(pbuf + 11, "%d", &nx);
			else if (*(pbuf + 12) == 'n')
				sscanf_s(pbuf + 13, "%d", &nx);

			m->verts_info.positions = new float[totalVerts * vx];
			if (tx != 0)
				m->verts_info.texCoords = new float[totalVerts * tx];
			if (nx != 0)
				m->verts_info.normals = new float[totalVerts * nx];

			m->verts_info.format = 100 * vx + 10 * tx + nx;

			float* pos = (float*)m->verts_info.positions;
			float* tex = (float*)m->verts_info.texCoords;
			float* nrm = (float*)m->verts_info.normals;

			i = 0;
			do {
				fgets(buf, sizeof(buf), file); //<V>
				pbuf = strstr(buf, "t");//t=
				if (pbuf)
				{
					switch (tx)
					{
					case 1:
						sscanf_s(pbuf + 3, "%f", tex);
						break;
					case 2:
						sscanf_s(pbuf + 3, "%f%f", tex, tex + 1);
						break;
					case 3:
						sscanf_s(pbuf + 3, "%f%f%f", tex, tex + 1, tex + 2);
						break;
					default:
						break;
					}
				}

				tex += tx;

				pbuf = strstr(buf, "n");//n=
				if (pbuf)
				{
					switch (nx)
					{
					case 2:
						sscanf_s(pbuf + 3, "%f%f", nrm, nrm + 1);
						break;
					case 3:
						sscanf_s(pbuf + 3, "%f%f%f", nrm, nrm + 1, nrm + 2);
						break;
					default:
						break;
					}
				}
				nrm += nx;

				pbuf = strstr(buf, ">");
				switch (vx)
				{
				case 2:
					sscanf_s(pbuf + 1, "%f%f", pos, pos + 1);
					break;
				case 3:
					sscanf_s(pbuf + 1, "%f%f%f", pos, pos + 1, pos + 2);
					break;
				case 6:
					sscanf_s(pbuf + 1, "%f%f%f%f%f%f", pos, pos + 1, pos + 2, pos + 3, pos + 4, pos + 5);
					break;
				default:
					assert(0);
				}
				pos += vx;
			} while (++i < totalVerts);//</V>

			fgets(buf, sizeof(buf), file);//</Verts>

			pg = &m->head;
			fgets(buf, sizeof(buf), file);//<Group

			while (1)
			{
				pbuf = strstr(buf, "n");//name=
				i = MakeString(pbuf + 6, (char**)&pg->name, "\"");

				pbuf = strstr(pbuf + i + 8, "mat");//material=
				if (pbuf)
				{
					i = MakeString(pbuf + 10, &material, "\"");
					pg->suface = GetSurface(material);
				}

				pbuf = strstr(pbuf + i + 12, "s");//size=
				sscanf_s(pbuf + 6, "%u", &total);
				pg->size = total;

				pbuf = strstr(pbuf, "ebo");//ebo=
				sscanf_s(pbuf + 5, "%u", &ebo);
				pg->ebo = ebo;
				//printf("ebo = %d\n", pg->ebo);

				fgets(buf, sizeof(buf), file);//<Tris
				sscanf_s(&buf[13], "%u", &total);

				if (total)
				{
					pg->tris.total = total;
					pg->tris.elems = new unsigned int[3 * total];
					pu = (unsigned int*)pg->tris.elems;

					i = 0;
					do {
						fgets(buf, sizeof(buf), file);//<F>
						sscanf_s(&buf[3], "%u%u%u", &u1, &u2, &u3);
						pu[0] = u1 - 1;
						pu[1] = u2 - 1;
						pu[2] = u3 - 1;
						pu += 3;
					} while (++i < total);
				}
				fgets(buf, sizeof(buf), file);//</Tris>

				fgets(buf, sizeof(buf), file);//<Quads
				sscanf_s(&buf[14], "%d", &total);
				if (total)
				{
					pg->quads.total = total;
					pg->quads.elems = new unsigned int[4 * total];
					pu = (unsigned int*)pg->quads.elems;

					i = 0;
					do {
						fgets(buf, sizeof(buf), file);//<F>
						sscanf_s(&buf[3], "%u%u%u%u", &u1, &u2, &u3, &u4);
						pu[0] = u1 - 1;
						pu[1] = u2 - 1;
						pu[2] = u3 - 1;
						pu[3] = u4 - 1;
						pu += 4;
					} while (++i < total);
				}
				fgets(buf, sizeof(buf), file);//</Quads>
				fgets(buf, sizeof(buf), file);//</Group>
				fgets(buf, sizeof(buf), file);//<Group

				if (buf[1] == 'G')
				{
					pg->nextGroup = new struct Mesh_Info::Group_Info;
					pg = pg->nextGroup;
				}
				else
				{
					break;
				}
			}

			fclose(file);
			return true;
		}

		void FreeMeshInfo(Mesh_Info* m)
		{
			if (m == nullptr)
				return;

			struct Mesh_Info::Group_Info *curr = m->head.nextGroup,
				*next;

			if (m->head.tris.elems)
				delete[] m->head.tris.elems;
			if (m->head.quads.elems)
				delete[] m->head.quads.elems;
			{
				if (m->head.suface)
				{
					if (m->head.suface->bump)
						delete m->head.suface->bump;
					if (m->head.suface->map_bump)
						delete m->head.suface->map_bump;
					if (m->head.suface->map_d)
						delete m->head.suface->map_d;
					if (m->head.suface->map_ka)
						delete m->head.suface->map_ka;
					if (m->head.suface->map_kd)
						delete m->head.suface->map_kd;
					if (m->head.suface->map_ke)
						delete m->head.suface->map_ke;
					if (m->head.suface->map_ks)
						delete m->head.suface->map_ks;
					if (m->head.suface->map_ni)
						delete m->head.suface->map_ni;
					if (m->head.suface->map_ns)
						delete m->head.suface->map_ns;
				}
			}

			while (curr)
			{
				if (curr->tris.elems)
					delete[] curr->tris.elems;
				if (curr->quads.elems)
					delete[] curr->quads.elems;

				{
					if (curr->suface)
					{
						if (curr->suface->bump)
							delete curr->suface->bump;
						if (curr->suface->map_bump)
							delete curr->suface->map_bump;
						if (curr->suface->map_d)
							delete curr->suface->map_d;
						if (curr->suface->map_ka)
							delete curr->suface->map_ka;
						if (curr->suface->map_kd)
							delete curr->suface->map_kd;
						if (curr->suface->map_ke)
							delete curr->suface->map_ke;
						if (curr->suface->map_ks)
							delete curr->suface->map_ks;
						if (curr->suface->map_ni)
							delete curr->suface->map_ni;
						if (curr->suface->map_ns)
							delete curr->suface->map_ns;
					}
				}

				next = curr->nextGroup;
				delete curr;
				curr = next;
			}

			FreeVertsInfo(&m->verts_info);
		}

		void FreeVertsInfo(Mesh_Info::Verts_Info* v)
		{
			if (v->positions)
				delete[] v->positions;
			if (v->texCoords)
				delete[] v->texCoords;
			if (v->normals)
				delete[] v->normals;
		}

	}
}
#include"render.h"
#include"..\Utils\utils.h"
#include"..\..\Dependencies\glew\glew.h"
#include"..\..\Dependencies\freeglut\freeglut.h"
#include<stdio.h>
#include<assert.h>

#define BUFFER_OFFSET(offset) ((GLvoid*)( NULL + offset))
#define NumberOf(array) (sizeof(array)/sizeof(array[0]))


namespace uee
{
	namespace graphx
	{

		RENDER_INFO* GetRenderInfo(Mesh_Info* mesh)
		{
			RENDER_INFO *r = new RENDER_INFO();
			GLvoid *vptr, *tptr, *nptr;
			GLuint bytes, bytesX2, bytesX3, bytesX6;
			char *vShaderStr = 0, *fShaderStr = 0, *pv = 0, *pf = 0;

			bytes = sizeof(float) * mesh->verts_info.total;
			bytesX2 = bytes * 2;
			bytesX3 = bytes * 3;
			bytesX6 = bytes * 6;

			vptr = mesh->verts_info.positions;
			tptr = mesh->verts_info.texCoords;
			nptr = mesh->verts_info.normals;
			r->format = (ARRAY_FORMAT)mesh->verts_info.format;

			glGenVertexArrays(1, &r->vao);

			switch (r->format)
			{
			case V2T0N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, vptr, GL_STATIC_DRAW);
				break;
			case V2T2N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, vptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, tptr, GL_STATIC_DRAW);
				break;
			case V2T3N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, tptr, GL_STATIC_DRAW);
				break;
			case V2T0N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V2T2N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, vptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, tptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[2].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[2].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V2T3N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, vptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, tptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[2].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[2].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V3T0N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, vptr, GL_STATIC_DRAW);
				break;
			case V3T2N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, tptr, GL_STATIC_DRAW);
				break;
			case V3T3N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, tptr, GL_STATIC_DRAW);
				break;
			case V3T0N3:

				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V3T2N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, vptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, tptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[2].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[2].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V3T3N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, tptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[2].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[2].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V6T0N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX6, vptr, GL_STATIC_DRAW);
				break;
			case V6T2N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX6, vptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, tptr, GL_STATIC_DRAW);
				break;
			case V6T3N0:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX6, vptr, GL_STATIC_DRAW);

				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, tptr, GL_STATIC_DRAW);
				break;
			case V6T0N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX6, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V6T2N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX6, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX2, tptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[2].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[2].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			case V6T3N3:
				glGenBuffers(1, &r->aBuffers[0].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[0].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX6, vptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[1].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[1].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, tptr, GL_STATIC_DRAW);


				glGenBuffers(1, &r->aBuffers[2].vbo);
				glBindBuffer(GL_ARRAY_BUFFER, r->aBuffers[2].vbo);
				glBufferData(GL_ARRAY_BUFFER, bytesX3, nptr, GL_STATIC_DRAW);
				break;
			default:
				break;
			}

			glBindBuffer(GL_ARRAY_BUFFER, NULL);

			{
				struct Mesh_Info::Group_Info* pg = &mesh->head;
				unsigned ebo, max_ebo = 0;
				while (pg)
				{
					ebo = pg->ebo;
					if (ebo > max_ebo)
						max_ebo = ebo;
					assert(ebo < MAX_ELEMENT_ARRAY_BUFFER_SIZE);
					r->eaBuffers[ebo].tricount += pg->tris.total;
					r->eaBuffers[ebo].quadcount += pg->quads.total;
					if (r->eaBuffers[ebo].surface == nullptr)
					{
						r->eaBuffers[ebo].surface = pg->suface;
						if (pg->suface && !pg->suface->map_kd && !pg->suface->map_bump
							&& !pg->suface->bump)
						{
							r->eaBuffers[ebo].shader = GetShaderInfo(ShaderType::LIGHTING_ONLY);
						}
						else if (pg->suface && pg->suface->map_kd)
						{
							if (pg->suface->map_bump || pg->suface->bump)
								r->eaBuffers[ebo].shader = GetShaderInfo(ShaderType::TEXURE_WITH_LIGHTING_AND_BUMP_MAP);
							else if (pg->suface->map_d)
								r->eaBuffers[ebo].shader = GetShaderInfo(ShaderType::TEXURE_WITH_LIGHTING_AND_BLENDING);
							else
								r->eaBuffers[ebo].shader = GetShaderInfo(ShaderType::TEXURE_WITH_LIGHTING);
						}
					}

					pg = pg->nextGroup;
				}

				r->element_array_size = ++max_ebo;


				for (unsigned i = 0, k = 0; i < max_ebo; ++i)
				{
					GLuint* tris, *quads, *temp;
					GLuint len = (3 * r->eaBuffers[i].tricount) + (4 * r->eaBuffers[i].quadcount);

					pg = &mesh->head;

					glGenBuffers(1, &r->eaBuffers[i].ebo);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->eaBuffers[i].ebo);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*len, NULL, GL_STATIC_DRAW);
					tris = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

					if (tris == NULL) {
						fprintf(stderr, "Unable to map index buffer\n");
						exit(EXIT_FAILURE);
					}

					quads = tris + (3 * r->eaBuffers[i].tricount);

					while (pg)
					{
						if (pg->ebo == i)
						{
							if (pg->tris.elems)
							{
								temp = (GLuint*)pg->tris.elems;
								for (k = 0; k < pg->tris.total; ++k)
								{
									*tris++ = *temp++;
									*tris++ = *temp++;
									*tris++ = *temp++;
								}
							}
							if (pg->quads.elems)
							{
								temp = (GLuint*)pg->quads.elems;
								for (k = 0; k < pg->quads.total; ++k)
								{
									*quads++ = *temp++;
									*quads++ = *temp++;
									*quads++ = *temp++;
									*quads++ = *temp++;
								}
							}
						}

						pg = pg->nextGroup;
					}

					glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
			}

			glBindVertexArray(r->vao);
			BindArrayBuffers(r->aBuffers, r->format);
			glBindVertexArray(0);
			return r;
		}


		void BindArrayBuffers(RENDER_INFO::Array_Buffer b[], ARRAY_FORMAT fmt)
		{
			Shader_Info::Attribs::Locations* loc = &Shader_Info::attribs.locations;
			int stride;

			switch (fmt)
			{
			case V2T0N0:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);
				break;
			case V2T2N0:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);
				break;
			case V2T3N0:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);
				break;
			case V2T0N3:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V2T2N3:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);

				glBindBuffer(GL_ARRAY_BUFFER, b[2].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V2T3N3:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);

				glBindBuffer(GL_ARRAY_BUFFER, b[2].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V3T0N0:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);
				break;
			case V3T2N0:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);
				break;
			case V3T3N0:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);
				break;
			case V3T0N3:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V3T2N3:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);

				glBindBuffer(GL_ARRAY_BUFFER, b[2].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V3T3N3:
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);

				glBindBuffer(GL_ARRAY_BUFFER, b[2].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V6T0N0:
				stride = 3 * sizeof(float);
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->color, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(stride));
				glEnableVertexAttribArray(loc->color);
				break;
			case V6T2N0:
				stride = 3 * sizeof(float);
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->color, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(stride));
				glEnableVertexAttribArray(loc->color);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);
				break;
			case V6T3N0:
				stride = 3 * sizeof(float);
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->color, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(stride));
				glEnableVertexAttribArray(loc->color);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);
				break;
			case V6T0N3:
				stride = 3 * sizeof(float);
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->color, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(stride));
				glEnableVertexAttribArray(loc->color);

				glBindBuffer(GL_ARRAY_BUFFER, b[2].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V6T2N3:
				stride = 3 * sizeof(float);
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->color, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(stride));
				glEnableVertexAttribArray(loc->color);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 2, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);

				glBindBuffer(GL_ARRAY_BUFFER, b[2].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			case V6T3N3:
				stride = 3 * sizeof(float);
				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->position, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->position);

				glBindBuffer(GL_ARRAY_BUFFER, b[0].vbo);
				glVertexAttribPointer(loc->color, 3, GL_FLOAT, false, stride, BUFFER_OFFSET(stride));
				glEnableVertexAttribArray(loc->color);

				glBindBuffer(GL_ARRAY_BUFFER, b[1].vbo);
				glVertexAttribPointer(loc->texCoord, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->texCoord);

				glBindBuffer(GL_ARRAY_BUFFER, b[2].vbo);
				glVertexAttribPointer(loc->normal, 3, GL_FLOAT, false, 0, BUFFER_OFFSET(0));
				glEnableVertexAttribArray(loc->normal);
				break;
			default:
				printf("Something is Seriously wrong!!!!!!!!!\n");
				break;
			}
		}

		void DrawElementArrayBuffer(RENDER_INFO::Element_Array_Buffer e)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.ebo);
			if (e.tricount)
				glDrawElements(GL_TRIANGLES, 3 * e.tricount, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
			if (e.quadcount)
				glDrawElements(GL_QUADS, 4 * e.quadcount, GL_UNSIGNED_INT, BUFFER_OFFSET(3 * sizeof(GL_UNSIGNED_INT)*e.tricount));
		}

		void Render(RENDER_INFO* r)
		{
			glBindVertexArray(r->vao);

			for (unsigned i = 0; i < r->element_array_size; ++i)//These can be Multithreaded
			{
				Shader_Info* shader = r->eaBuffers[i].shader;
				Shader_Info::Uniforms::Locations* loc = &shader->uniforms.locations;
				if (shader)/////////////////////////////////
					glUseProgram(shader->program.object);
				
				//Set the Surface Material Properties Uniforms
				if (r->eaBuffers[i].surface)
				{
					if (shader->program.version > VERSION_1_0)
					{
						Texture2D::BindTexure(GL_TEXTURE0, r->eaBuffers[i].surface->map_kd);
						glUniform1i(loc->mapKd, 0);

						if (r->eaBuffers[i].surface->map_bump)
						{
							Texture2D::BindTexure(GL_TEXTURE1, r->eaBuffers[i].surface->map_bump);
							glUniform1i(loc->mapBump, 1);
						}
						else if (r->eaBuffers[i].surface->bump)
						{
							Texture2D::BindTexure(GL_TEXTURE1, r->eaBuffers[i].surface->bump);
							glUniform1i(loc->mapBump, 1);
						}
						else if (r->eaBuffers[i].surface->map_d)
						{
							Texture2D::BindTexure(GL_TEXTURE1, r->eaBuffers[i].surface->map_d);
							glUniform1i(loc->mapD, 1);
							glBlendEquation(GL_FUNC_ADD);
							glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						}
					}

					glUniform3f(loc->matAmbient, r->eaBuffers[i].surface->ka[0],
						r->eaBuffers[i].surface->ka[1],
						r->eaBuffers[i].surface->ka[2]);

					glUniform3f(loc->matDiffuse, r->eaBuffers[i].surface->kd[0],
						r->eaBuffers[i].surface->kd[1],
						r->eaBuffers[i].surface->kd[2]);

					glUniform3f(loc->matSpecular, r->eaBuffers[i].surface->ks[0],
						r->eaBuffers[i].surface->ks[1],
						r->eaBuffers[i].surface->ks[2]);

					glUniform1f(loc->matShininess, r->eaBuffers[i].surface->ns);
					glUniform1f(loc->matDissolve, r->eaBuffers[i].surface->d);
				}
				DrawElementArrayBuffer(r->eaBuffers[i]);
			}
		}
	}
}
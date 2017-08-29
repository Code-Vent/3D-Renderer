#ifndef UEE_RENDER_H
#define UEE_RENDER_H

#include"..\Shader\shader.h"
using namespace uee::shader;
#include"meshInfo.h"



#define MAX_ARRAY_BUFFER_SIZE 3
#define MAX_ELEMENT_ARRAY_BUFFER_SIZE 16

namespace uee
{
	namespace graphx
	{
		enum ARRAY_FORMAT {
			V2T0N0 = 200,
			V2T2N0 = 220,
			V2T3N0 = 230,
			V2T0N3 = 203,
			V2T2N3 = 223,
			V2T3N3 = 233,
			V3T0N0 = 300,
			V3T2N0 = 320,
			V3T3N0 = 330,
			V3T0N3 = 303,
			V3T2N3 = 323,
			V3T3N3 = 333,
			V6T0N0 = 600,
			V6T2N0 = 620,
			V6T3N0 = 630,
			V6T0N3 = 603,
			V6T2N3 = 623,
			V6T3N3 = 633,
		};

		typedef struct Render_Info
		{
			ARRAY_FORMAT format;
			unsigned int element_array_size;
			unsigned int vao = -1;
			struct Array_Buffer
			{
				unsigned int vbo = -1;
			}aBuffers[MAX_ARRAY_BUFFER_SIZE];

			struct Element_Array_Buffer
			{
				unsigned int ebo = -1;
				unsigned int tricount = 0;
				unsigned int quadcount = 0;
				const Surface_Info* surface = nullptr;
				Shader_Info *shader;
			}eaBuffers[MAX_ELEMENT_ARRAY_BUFFER_SIZE];

		}RENDER_INFO;

		void BindArrayBuffers(RENDER_INFO::Array_Buffer b[], ARRAY_FORMAT fmt);
		void DrawElementArrayBuffer(RENDER_INFO::Element_Array_Buffer e);
		RENDER_INFO* GetRenderInfo(Mesh_Info* mesh);
		void Render(RENDER_INFO* r);
	}
}
#endif
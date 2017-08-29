#ifndef UEE_MODEL_3D_H
#define UEE_MODEL_3D_H

#include<stdlib.h>
#include"..\Graphics\meshInfo.h"
#include"..\Shader\shader.h"
#include"..\Graphics\render.h"


using namespace uee::graphx;

namespace uee
{
	namespace entity
	{
		class Model3D
		{
		public:
			void DrawMesh();

			Mesh_Info* mesh_info = NULL;
			Shader_Info* shader_info = NULL;
			RENDER_INFO* irender;
		};

	}
}

#endif

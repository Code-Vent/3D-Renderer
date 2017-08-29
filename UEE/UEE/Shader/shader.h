#ifndef UEE_SHADER_H
#define UEE_SHADER_H

#define VERSION_1_0 10
#define VERSION_2_0 20

namespace uee
{
	namespace shader
	{
		enum ShaderType {
			LIGHTING_ONLY,
			TEXURE_WITH_LIGHTING,
			TEXURE_WITH_LIGHTING_AND_BLENDING,
			TEXURE_WITH_LIGHTING_AND_BUMP_MAP
		};

		typedef struct Shader_Info
		{
			struct Program
			{
				unsigned int object = 0;
				int linkStatus = 0;
				char* log = nullptr;
				int version;
			}program;

			static struct Attribs
			{
				struct Locations
				{
					const int position = 0;
					const int normal = 1;
					const int texCoord = 2;
					const int color = 3;
				}locations;

				struct Identifiers
				{
					const char* const Position = "aPosition";
					const char* const Normal = "aNormal";
					const char* const TexCoord = "aTexCoord";
					const char* const Color = "aColor";
				}identifiers;
			}attribs;

			struct Uniforms
			{
				struct Locations
				{
					int projectionMat;
					int viewMat;
					int modelMat;
					int matAmbient;
					int matDiffuse;
					int matSpecular;
					int matShininess;
					int matDissolve;
					int mapBump;
					int mapKa;
					int mapKd;
					int mapKs;
					int mapKe;
					int mapD;
					int mapNi;
					int mapNs;
					int bump;
				}locations;

				static struct Identifiers
				{
					char* const projectionMat = "uProjectionMat";
					char* const viewMat = "uViewMat";
					char* const modelMat = "uModelMat";
					char* const matAmbient = "uMatAmbient";
					char* const matDiffuse = "uMatDiffuse";
					char* const matSpecular = "uMatSpecular";
					char* const matShininess = "uMatShininess";
					char* const matDissolve = "uMatDissolve";
					char* const mapBump = "uMapBump";
					char* const mapKa = "uMapKa";
					char* const mapKd = "uMapKd";
					char* const mapKs = "uMapKs";
					char* const mapKe = "uMapKe";
					char* const mapD = "uMapD";
					char* const mapNi = "uMapNi";
					char* const mapNs = "uMapNs";
					char* const bump = "uBump";
				}identifiers;
			}uniforms;
		}SHADER_INFO;

		Shader_Info* CreateShader(const char* vertexSrc, const char* fragmentSrc, int version = VERSION_1_0);

		Shader_Info* GetShaderInfo(ShaderType type);


	}
}
#endif
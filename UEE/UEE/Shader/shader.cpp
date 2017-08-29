#include"shader.h"
#include"..\Utils\utils.h"
#include"..\..\Dependencies\glew\glew.h"
#include"..\..\Dependencies\freeglut\freeglut.h"
#include<stdio.h>
#include<assert.h>

using namespace uee::utils;

namespace uee
{
	namespace shader
	{
#define NUMBER_OF_SHADERS 4

		Shader_Info::Attribs Shader_Info::attribs;
		Shader_Info::Uniforms::Identifiers Shader_Info::Uniforms::identifiers;

		const char *vertexSrc[NUMBER_OF_SHADERS] = {
			"Shader/simpleBumpMapped.vert.cpp",
			"Shader/simpleFragmentTextured.vert.cpp",
			"Shader/simpleVertexLighting.vert.cpp",
			"Shader/simpleFragmentTextured.vert.cpp"
		};

		const char *fragmentSrc[NUMBER_OF_SHADERS] = {
			"Shader/simpleBumpMapped.frag.cpp",
			"Shader/simpleFragmentTextured.frag.cpp",
			"Shader/simpleVertexLighting.frag.cpp",
			"Shader/simpleFragmentTexturedBlended.frag.cpp"
		};

		const unsigned versions[NUMBER_OF_SHADERS] = {
			VERSION_2_0,
			VERSION_2_0,
			VERSION_1_0,
			VERSION_2_0
		};

		struct ShaderFactory
		{
			ShaderFactory();
			~ShaderFactory();
			Shader_Info* GetShader(ShaderType type);
			void MakeShader(int index);
		private:
			Shader_Info* shaders[NUMBER_OF_SHADERS];

		}shaderFactory;

		GLuint LoadShader(GLenum type, const char* shaderSrc, char** infoLog)
		{
			GLuint shader;
			GLint compiled;

			shader = glCreateShader(type);

			int q = 0;
			if (shader == 0)
				return 0;
			glShaderSource(shader, 1, &shaderSrc, NULL);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

			if (!compiled)
			{
				//Log Error info and delete shader
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
				if (infoLen > 1)
				{
					if (*infoLog)
						delete *infoLog;

					*infoLog = new char[infoLen + 1];
					glGetShaderInfoLog(shader, infoLen, NULL, *infoLog);
					fprintf(stderr, "Error compiling shader:\n%s\n", *infoLog);
				}
				glDeleteShader(shader);
				return 0;
			}
			return shader;
		}

		Shader_Info * CreateShader(const char * vertexSrc, const char * fragmentSrc, int version)
		{
			Shader_Info* shaderInfo = new Shader_Info();
			GLuint vertexShader;
			GLuint fragmentShader;
			GLuint programObject;

			vertexShader = LoadShader(GL_VERTEX_SHADER, vertexSrc, &shaderInfo->program.log);
			fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentSrc, &shaderInfo->program.log);

			programObject = glCreateProgram();

			if (programObject == 0)
				return 0;

			glAttachShader(programObject, vertexShader);
			glAttachShader(programObject, fragmentShader);
			glLinkProgram(programObject);

			glGetProgramiv(programObject, GL_LINK_STATUS, &shaderInfo->program.linkStatus);

			if (!shaderInfo->program.linkStatus)
			{
				//Log Error and delete vertex and fragment Shaders
				GLint infoLen = 0;
				glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

				if (infoLen > 1)
				{
					if (shaderInfo->program.log)
						delete shaderInfo->program.log;

					shaderInfo->program.log = new char[infoLen + 1];
					glGetProgramInfoLog(programObject, infoLen, NULL, shaderInfo->program.log);
					fprintf(stderr, "Error linking program:\n%s\n", shaderInfo->program.log);
				}
				glDeleteProgram(programObject);
			}

			shaderInfo->program.object = programObject;


			/*Get Uniforms Locations*/
			Shader_Info::Uniforms::Locations* loc1 = &shaderInfo->uniforms.locations;
			Shader_Info::Uniforms::Identifiers* name1 = &shaderInfo->uniforms.identifiers;
			{
				//Transform Matrices
				loc1->modelMat = glGetUniformLocation(programObject, name1->modelMat);
				loc1->viewMat = glGetUniformLocation(programObject, name1->viewMat);
				loc1->projectionMat = glGetUniformLocation(programObject, name1->projectionMat);
			}
			{
				//Material Properties
				loc1->matAmbient = glGetUniformLocation(programObject, name1->matAmbient);
				loc1->matDiffuse = glGetUniformLocation(programObject, name1->matDiffuse);
				loc1->matSpecular = glGetUniformLocation(programObject, name1->matSpecular);
				loc1->matShininess = glGetUniformLocation(programObject, name1->matShininess);
				loc1->matDissolve = glGetUniformLocation(programObject, name1->matDissolve);
			}

			if (version > VERSION_1_0)
			{
				//Maps
				loc1->mapBump = glGetUniformLocation(programObject, name1->mapBump);
				loc1->mapD = glGetUniformLocation(programObject, name1->mapD);
				loc1->mapKa = glGetUniformLocation(programObject, name1->mapKa);
				loc1->mapKd = glGetUniformLocation(programObject, name1->mapKd);
				loc1->mapKs = glGetUniformLocation(programObject, name1->mapKs);
				loc1->mapKe = glGetUniformLocation(programObject, name1->mapKe);
				loc1->mapNi = glGetUniformLocation(programObject, name1->mapNi);
				loc1->mapNs = glGetUniformLocation(programObject, name1->mapNs);
				loc1->bump = glGetUniformLocation(programObject, name1->bump);

			}
			shaderInfo->program.version = version;
			return shaderInfo;
		}

		Shader_Info * GetShaderInfo(ShaderType type)
		{
			return shaderFactory.GetShader(type);
		}

		Shader_Info * ShaderFactory::GetShader(ShaderType type)
		{
			switch (type)
			{
			case LIGHTING_ONLY:
				if (!shaders[2])
					MakeShader(2);
				return shaders[2];
			case TEXURE_WITH_LIGHTING:
				if (!shaders[1])
					MakeShader(1);
				return shaders[1];
			case TEXURE_WITH_LIGHTING_AND_BUMP_MAP:
				if (!shaders[0])
					MakeShader(0);
				return shaders[0];
			case TEXURE_WITH_LIGHTING_AND_BLENDING:
				if (!shaders[3])
					MakeShader(3);
				return shaders[3];
			default:
				return shaders[2];
			}
		}

		void ShaderFactory::MakeShader(int i)
		{
			char *pv, *pf, *vShaderStr, *fShaderStr;
			vShaderStr = ReadShaderFile(vertexSrc[i], &pv);
			fShaderStr = ReadShaderFile(fragmentSrc[i], &pf);
			shaders[i] = CreateShader(vShaderStr, fShaderStr, versions[i]);
			if (pv)
				delete[] pv;
			if (pf)
				delete[] pf;
		}


		ShaderFactory::ShaderFactory()
		{
			for (int i = 0; i < NUMBER_OF_SHADERS; ++i)
			{
				shaders[i] = nullptr;
			}
		}

		ShaderFactory::~ShaderFactory()
		{
			for (int i = 0; i < NUMBER_OF_SHADERS; ++i)
			{
				if (shaders[i])
					delete shaders[i];
			}
		}

	}
}
#pragma once

#define in extern 
#define out static
#define uniform extern
#define core
#define $
#define version
#define _330

#define layout(l) 

#define VS_OUT struct
#define main static entry



struct vec2
{
	vec2() {}
	vec2(float, float) {}
	vec2(float f[]) {}
	union
	{
		struct
		{
			float x;
			float y;
		};
		struct
		{
			float u;
			float v;
		};
		float xy[2];
		float uv[2];
		float st[2];
	};

};

struct vec3
{
	vec3() {}
	vec3(float, float, float) {}
	vec3(float f[]) {}

	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float r;
			float g;
			float b;
		};
		float xyz[3];
		float rgb[3];
	};

	vec3 operator*(vec3) { return vec3(); }
	vec3 operator+(vec3) { return vec3(); }
	vec3 operator-(vec3) { return vec3(); }
	vec3 operator-() { return *this; }
};

struct vec4
{
	vec4() {}
	vec4(vec3, float) {}
	vec4(float, float, float, float) {}
	vec4(float f[]) {}
	explicit operator vec3 () { return vec3(); }

	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		struct
		{
			vec3 xyz;
			float w;
		};
		struct
		{
			vec3 rgb;
			float a;
		};
		struct
		{
			vec2 st;
			vec2 rq;
		};
		float rgba[4];
		float xyzw[4];
	};

	vec4 operator*(vec4) { return vec4(); }
	vec4 operator+(vec4) { return vec4(); }
	vec4 operator-(vec4) { return vec4(); }
	vec4 operator-() { return *this; }
};

vec3 operator*(float, vec3);
vec4 operator*(float, vec4);
vec3 operator*(vec3, vec4);

struct mat3
{
	vec3 operator*(vec3) { return vec3(); }
	mat3 operator*(mat3) { return mat3(); }
};

struct mat4 : public mat3
{
	vec4 operator*(vec4) { return vec4(); }
	mat4 operator*(mat4) { return mat4(); }
};

struct sampler1D
{

};

struct sampler2D
{

};

struct sampler3D
{

};

vec4 texture1D(sampler1D sampler, float coord);
vec4 texture1D(sampler1D sampler, float coord, float bias);
vec4 texture2D(sampler2D sampler, vec2 coord);
vec4 texture2D(sampler2D sampler, vec2 coord, float bias);
vec4 texture3D(sampler3D sampler, vec3 coord);
vec4 texture3D(sampler3D sampler, vec3 coord, float bias);


vec3 normalize(vec3);
vec3 reflect(vec3, vec3);
float dot(vec3, vec3);
vec3 cross(vec3, vec3);
float max(float, float);
float pow(float, float);
vec4 clamp(vec4, float, float);
vec4 clamp(vec4, vec4, vec4);
vec4 mix(vec4, vec4, float);
vec4 step(vec4, vec4);
vec4 smoothstep(vec4, vec4, vec4);



//In-built values
extern struct vec4 gl_Position, gl_FragColor;
extern struct mat4 gl_ModelViewMatrix, gl_ProjectionMatrix;
extern struct vec3 gl_Vertex;
extern struct mat3 gl_NormalMatrix;

//Attributes
extern vec4 aPosition, aColor, aTexCoord;
extern vec3 aNormal;

//Uniforms
extern vec3 uMatAmbient;
extern vec3 uMatDiffuse;
extern vec3 uMatSpecular;
extern float uMatShininess, uMatDissolve;
extern struct mat4 uProjectionMat, uViewMat, uModelMat;
extern struct sampler2D uMapBump;
extern struct sampler2D uMapKa;
extern struct sampler2D uMapKd;
extern struct sampler2D uMapKs;
extern struct sampler2D uMapKe;
extern struct sampler2D uMapD;
extern struct sampler2D uMapNi;
extern struct sampler2D uMapNs;
extern struct sampler2D uBump;


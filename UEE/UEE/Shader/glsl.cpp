#include"glsl.h"

//In-built values
struct vec3 gl_Vertex;
struct vec4 gl_Position, gl_FragColor;
struct mat4 gl_ModelViewMatrix, gl_ProjectionMatrix;
struct mat3 gl_NormalMatrix;

//Attributes
struct vec4 aPosition, aColor, aTexCoord;
struct vec3 aNormal;

//Uniforms
struct vec3 uMatAmbient;
struct vec3 uMatDiffuse;
struct vec3 uMatSpecular;
float uMatShininess, uMatDissolve;
struct mat4 uProjectionMat, uViewMat, uModelMat;
struct sampler2D uMapBump;
struct sampler2D uMapKa;
struct sampler2D uMapKd;
struct sampler2D uMapKs;
struct sampler2D uMapKe;
struct sampler2D uMapD;
struct sampler2D uMapNi;
struct sampler2D uMapNs;
struct sampler2D uBump;

vec3 operator*(float, vec3) { return vec3(); }
vec4 operator*(float, vec4) { return vec4(); }
vec3 operator*(vec3, vec4) { return vec3(); }

vec3 normalize(vec3) { return vec3(); }
vec3 reflect(vec3, vec3) { return vec3(); }
float dot(vec3, vec3) { return 0.0; }
vec3 cross(vec3, vec3) { return vec3(); }
float max(float, float) { return 0.0; }
float pow(float, float) { return 0.0; }
vec4 clamp(vec4 x, float minVal, float maxVal)
{
	return vec4();
}
vec4 clamp(vec4 x, vec4 minVal, vec4 maxVal)
{
	return vec4();
}

vec4 mix(vec4 x, vec4 y, float a)
{
	return vec4();
}

vec4 step(vec4 edge, vec4 x)
{
	return vec4();
}

vec4 smoothstep(vec4 edge0, vec4 edge1, vec4 x)
{
	return vec4();
}

vec4 texture1D(sampler1D sampler, float coord)
{
	return vec4();
}
vec4 texture1D(sampler1D sampler, float coord, float bias)
{
	return vec4();
}
vec4 texture2D(sampler2D sampler, vec2 coord)
{
	return vec4();
}
vec4 texture2D(sampler2D sampler, vec2 coord, float bias)
{
	return vec4();
}
vec4 texture3D(sampler3D sampler, vec3 coord)
{
	return vec4();
}
vec4 texture3D(sampler3D sampler, vec3 coord, float bias)
{
	return vec4();
}
#include"glsl.h"

$ version _330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aTexCoord;


out VS_OUT
{
	vec3 N;
vec3 L;
vec3 V;
vec4 texCoord;
} vs_out;

void main()
{
	vec4 P = gl_ModelViewMatrix * aPosition;

	vs_out.N = mat3(gl_ModelViewMatrix) * aNormal;
	vs_out.L = vec3(0.0, 0.0, 1.0);
	vs_out.V = -P.xyz;
	vs_out.texCoord = aTexCoord;
	gl_Position = gl_ProjectionMatrix * P;
}
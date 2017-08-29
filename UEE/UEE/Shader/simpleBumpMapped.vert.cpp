#include"glsl.h"

$ version _330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aTexCoord;

out VS_OUT
{
	vec3 lightDir;
vec3 eyeDir;
vec2 texCoord;
} vs_out;

uniform vec3 light_pos = vec3(0.0, 0.0, 100.0);

vec3 up = vec3(0.0, 1.0, 0.0);

void main()
{
	vec4 P = gl_ModelViewMatrix * aPosition;

	float mag = dot(aNormal, up);
	up = up - (mag * aNormal);

	vec3 N = normalize(mat3(gl_ModelViewMatrix) * aNormal);
	vec3 T = normalize(mat3(gl_ModelViewMatrix) * up);
	vec3 B = cross(N, T);

	vec3 L = light_pos - P.xyz;
	vs_out.lightDir = normalize(vec3(dot(L, T), dot(L, B), dot(L, N)));

	vec3 V = -P.xyz;
	vs_out.eyeDir = normalize(vec3(dot(V, T), dot(V, B), dot(V, N)));

	vs_out.texCoord = aTexCoord.st;

	gl_Position = gl_ProjectionMatrix * P;
}
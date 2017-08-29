#include"glsl.h"

$ version _330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec3 aNormal;

uniform vec3 uMatAmbient;
uniform vec3 uMatDiffuse;
uniform vec3 uMatSpecular;
uniform float uMatShininess;


out VS_OUT
{
	vec3 color;
} vs_out;

void main()
{
	vec4 P = gl_ModelViewMatrix * aPosition;
	vec3 N = mat3(gl_ModelViewMatrix) * aNormal;

	vec3 L = vec3(0.0, 0.7071, 0.7071);
	vec3 V = -P.xyz;

	N = normalize(N);
	L = normalize(L);
	V = normalize(V);

	vec3 R = reflect(-L, N);
	vec3 diffuse = max(dot(N, L), 0.0) * uMatDiffuse;
	vec3 specular = pow(max(dot(R, V), 0.0), uMatShininess) * uMatSpecular;
	vs_out.color = uMatAmbient + diffuse + specular;

	gl_Position = gl_ProjectionMatrix * P;
}
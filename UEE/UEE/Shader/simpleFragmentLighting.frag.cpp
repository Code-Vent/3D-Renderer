#include"glsl.h"

$ version _330

layout(location = 0) out vec4 color;

uniform vec3 uMatAmbient;
uniform vec3 uMatDiffuse;
uniform vec3 uMatSpecular;
uniform float uMatShininess;
uniform float uMatDissolve;

in VS_OUT
{
	vec3 N;
vec3 L;
vec3 V;
}fs_in;


void main()
{
	vec3 N = normalize(fs_in.N);
	vec3 L = normalize(fs_in.L);
	vec3 V = normalize(fs_in.V);
	vec3 H = normalize(L + V);

	vec3 diffuse = max(dot(N, L), 0.0) * uMatDiffuse;
	vec3 specular = pow(max(dot(N, H), 0.0), uMatShininess) *
		uMatSpecular;
	color = vec4(uMatAmbient + diffuse + specular, uMatDissolve);
}
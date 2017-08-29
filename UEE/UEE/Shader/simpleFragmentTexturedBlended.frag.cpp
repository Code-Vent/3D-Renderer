#include"glsl.h"

$ version _330 core

layout(location = 0) out vec4 color;

uniform vec3 uMatAmbient;
uniform vec3 uMatDiffuse;
uniform vec3 uMatSpecular;
uniform float uMatShininess;
uniform float uMatDissolve;

//uniform sampler2D uMapBump;
//uniform sampler2D uMapKa;
uniform sampler2D uMapKd;
//uniform sampler2D uMapKs;
//uniform sampler2D uMapKe;
uniform sampler2D uMapD;
//uniform sampler2D uMapNi;
//uniform sampler2D uMapNs;
//uniform sampler2D uBump;

in VS_OUT
{
	vec3 N;
vec3 L;
vec3 V;
vec4 texCoord;
} fs_in;

void main()
{
	vec3 N = normalize(fs_in.N);
	vec3 L = normalize(fs_in.L);
	vec3 V = normalize(fs_in.V);
	vec3 H = normalize(L + V);

	vec3 diffuse_albedo = uMatDiffuse * texture2D(uMapKd, fs_in.texCoord.st).rgb;
	vec3 diffuse = max(dot(N, L), 0.0) * vec3(diffuse_albedo);
	vec3 specular = pow(max(dot(N, H), 0.0), uMatShininess) *
		uMatSpecular;
	color = vec4(diffuse, texture2D(uMapD, fs_in.texCoord.st).a);
}
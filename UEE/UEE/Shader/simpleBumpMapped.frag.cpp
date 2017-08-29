#include"glsl.h"

$ version _330 core

layout(location = 0) out vec4 color;


uniform vec3 uMatAmbient;
uniform vec3 uMatDiffuse;
uniform vec3 uMatSpecular;
uniform float uMatShininess;
uniform float uMatDissolve;

uniform sampler2D uMapBump;
uniform sampler2D uMapKd;


in VS_OUT
{
	vec3 lightDir;
vec3 eyeDir;
vec2 texCoord;
} fs_in;

void main()
{
	vec3 V = normalize(fs_in.eyeDir);
	vec3 L = normalize(fs_in.lightDir);

	vec3 N = normalize(texture2D(uMapBump, fs_in.texCoord).rgb);// *2.0 vec3(1.0));
																// Calculate R ready for use in Phong lighting.
	vec3 R = reflect(-L, N);

	vec3 diffuse_albedo = uMatDiffuse * texture2D(uMapKd, fs_in.texCoord).rgb;
	// Calculate diffuse color with simple N dot L.
	vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;
	// Uncomment this to turn off diffuse shading
	// diffuse = vec3(0.0);

	// Calculate Phong specular highlight
	vec3 specular = max(pow(dot(R, V), uMatShininess), 0.0) * uMatSpecular;
	// Uncomment this to turn off specular highlights
	// specular = vec3(0.0);
	// Final color is diffuse + specular
	color = vec4(uMatAmbient + diffuse + specular, uMatDissolve);
}
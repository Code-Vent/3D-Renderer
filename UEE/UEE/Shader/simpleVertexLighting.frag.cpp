#include"glsl.h"

$ version _330 core

layout(location = 0) out vec4 color;

uniform float uMatDissolve;

in VS_OUT
{
	vec3 color;
} fs_in;

void main()
{
	color = vec4(fs_in.color, uMatDissolve);
}
#version 420 core

layout(location = 0) in vec3 a_Coord;
layout(location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Coord, 1.0f);
	v_TexCoord = a_TexCoord;
}
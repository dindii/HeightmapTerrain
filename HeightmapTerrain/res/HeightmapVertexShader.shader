#version 420 core

layout(location = 0) in vec3 a_Coord;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;

out float v_heightValue;
out vec2 v_TexCoord;

void main()
{
	v_heightValue = a_Coord.y;
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * vec4(a_Coord.x, a_Coord.y, a_Coord.z, 1.0f);
}
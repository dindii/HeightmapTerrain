#version 420 core

layout(location = 0) in vec3 a_Coord;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;


uniform mat4 u_ViewProjection;

out float v_heightValue;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
	v_heightValue = a_Coord.y;
	v_TexCoord = a_TexCoord;
	v_Normal = a_Normal;
	v_FragPos = a_Coord;

	gl_Position = u_ViewProjection * vec4(a_Coord.x, a_Coord.y, a_Coord.z, 1.0f);
}
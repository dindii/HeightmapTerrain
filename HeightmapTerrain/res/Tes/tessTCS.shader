#version 420 core

layout(vertices = 4) out;

in vec2 v_TexCoord[];

out vec2 TCS_TexCoord[];

void main()
{
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	TCS_TexCoord[gl_InvocationID] = v_TexCoord[gl_InvocationID];

	if (gl_InvocationID == 0)
	{
		gl_TessLevelOuter[0] = 16;
		gl_TessLevelOuter[1] = 16;
		gl_TessLevelOuter[2] = 16;
		gl_TessLevelOuter[3] = 16;

		gl_TessLevelInner[0] = 16;
		gl_TessLevelInner[1] = 16;
	}
}
#version 420 core

out vec4 finalColor;

in float v_heightValue;
in vec2 v_TexCoord;
uniform sampler2D u_Diffuse;

void main()
{
	float f_heightValue = (v_heightValue + 16) / 64.0f;
	finalColor = vec4(f_heightValue, f_heightValue, f_heightValue, 1.0f) * texture(u_Diffuse, v_TexCoord);
}
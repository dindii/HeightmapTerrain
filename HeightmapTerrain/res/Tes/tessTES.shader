#version 420 core

layout(quads, fractional_odd_spacing, cw) in;

uniform sampler2D u_Heightmap;
uniform mat4 u_ViewProjection;

in vec2 TCS_TexCoord[];

out float height;

void main()
{
	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	vec2 t00 = TCS_TexCoord[0];
	vec2 t01 = TCS_TexCoord[1];
	vec2 t10 = TCS_TexCoord[2];
	vec2 t11 = TCS_TexCoord[3];

	vec2 t0 = (t01 - t00) * u + t00;
	vec2 t1 = (t11 - t10) * u + t10;

	vec2 textureCoord = (t1 - t0) * v + t0;

	height = texture(u_Heightmap, textureCoord).y * 64.0f - 16.0f;


	vec4 p00 = gl_in[0].gl_Position;
	vec4 p01 = gl_in[1].gl_Position;
	vec4 p10 = gl_in[2].gl_Position;
	vec4 p11 = gl_in[3].gl_Position;

	vec4 uNorm = p01 - p00;
	vec4 vNorm = p10 - p00;
	vec4 normal = normalize(vec4(cross(vNorm.xyz, uNorm.xyz), 0));

	vec4 p0 = (p01 - p00) * u + p00;
	vec4 p1 = (p11 - p10) * u + p10;
	vec4 p =  (p1 - p0)   * v + p0;

	p += normal * height;

	gl_Position = u_ViewProjection * p;
}
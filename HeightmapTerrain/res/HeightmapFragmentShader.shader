#version 420 core

out vec4 finalColor;

in float v_heightValue;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D u_Diffuse;
uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;
uniform int u_ActivateAttenuation;
uniform int u_NormalView;

void main()
{
	if (u_NormalView > 0)
	{
		finalColor = vec4(v_Normal.xyz, 1.0f);
		return;
	}

	float lightConstantAttenuation = 1.0f;
	float lightLinearAttenuation = 0.18f;
	float lightQuadraticAttenuation = 0.016f;

	vec3 temporaryResult = vec3(0.0f, 0.0f, 0.0f);

	vec3 color = texture(u_Diffuse, v_TexCoord).rgb;
	vec3 ambient = 0.05f * color;

	//We will use a simple phong lighting here. Basically, the strength of the light is the dot product between the light position and the fragment's normal.
	vec3 lightPos = u_LightPos;
	vec3 lightDir = normalize(lightPos - v_FragPos);
	vec3 normal = v_Normal;

	float diffuseRate = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diffuseRate * color;

	float distance = length(lightPos - v_FragPos);
	float attenuation = 1.0f / (lightConstantAttenuation + lightLinearAttenuation * distance + lightQuadraticAttenuation * (distance * distance));
	
	vec3 ambientWithAttenuation = ambient * attenuation;
	vec3 diffuseWithAttenuation = diffuse * attenuation;

	if (u_ActivateAttenuation > 0)
	{
		temporaryResult = vec3(ambientWithAttenuation + diffuseWithAttenuation);
	}
	else
	{
		temporaryResult = vec3(ambient + diffuse);
	}

	//Set the color strength based on the height of the fragment.
	temporaryResult *= ((v_heightValue + 16) / 64.0f);

	finalColor = vec4(temporaryResult.xyz, 1.0f);
}
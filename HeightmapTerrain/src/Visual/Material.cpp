#include "Material.h"
#include <Rendering/Renderer.h>
#include <Resources/Texture2D.h>
#include <Light/FocalLight.h>

namespace Height
{
	//This is what allows us to have an optional texture. Without this, we would fetch a null texture, thus resulting in a black color (multiplying stuff by zero)
	static Texture2D* defaultWhiteTexture;

	Material::Material(const std::string& vertexpath, const std::string& fragpath, const std::string& tesControlSource, const std::string& tesEvaluationSource)
	{
		m_Shader = new Shader(vertexpath, fragpath, tesControlSource, tesEvaluationSource);
		
		if(!defaultWhiteTexture)
			defaultWhiteTexture = new Texture2D("res/defaultTexture.png");
		
		m_diffuseMap = defaultWhiteTexture;
	}

	Material::~Material()
	{
		delete m_Shader;
	}

	void Material::Bind() const
	{
		m_Shader->Bind();

		if (m_diffuseMap)
		{
			m_diffuseMap->Bind(EMapType::DIFFUSE_MAP);
			m_Shader->UploadInt("u_Diffuse", EMapType::DIFFUSE_MAP);
		}
	}

	void Material::SetViewProjection(const mat4& mat)
	{
		m_Shader->UploadUniformMat4("u_ViewProjection", mat);
	}

	void Material::SetLightContext(const FocalLight* light)
	{
		m_Shader->UploadUniformFloat3("u_LightPos", light->GetPosition());
	}

	void Material::SetCameraPos(const vec3& camPos)
	{
		m_Shader->UploadUniformFloat3("u_CameraPos", camPos);
	}

	void Material::ToggleAttenuation(bool toggle)
	{
		m_Shader->UploadInt("u_ActivateAttenuation", toggle);
	}

	void Material::AttachMap(Texture2D* map, EMapType mapType)
	{
		switch (mapType)
		{
		case EMapType::DIFFUSE_MAP:
		{
			m_diffuseMap = map;
		} break;

		default:
			std::cerr << "Warning: Unknown map type!" << std::endl;
		}
	}
}

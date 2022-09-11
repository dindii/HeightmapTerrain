#include "Material.h"
#include <Rendering/Renderer.h>
#include <Resources/Texture2D.h>

namespace Height
{
	static Texture2D* defaultWhiteTexture;

	Material::Material(const std::string& vertexpath, const std::string& fragpath)
	{
		m_Shader = new Shader(vertexpath, fragpath);
		
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

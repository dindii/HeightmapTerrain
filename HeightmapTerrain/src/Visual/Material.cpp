#include "Material.h"

namespace Height
{


	Material::Material(const std::string& vertexpath, const std::string& fragpath)
	{
		m_Shader = new Shader(vertexpath, fragpath);
	}

	Material::~Material()
	{
		delete m_Shader;

		//if (m_diffuseMap)
		//	delete m_diffuseMap;
	}

	void Material::Bind() const
	{
		m_Shader->Bind();

		//if (m_diffuseMap)
		//{
		//	m_diffuseMap->Bind(ERenderingMapSlot::Diffuse);
		//	m_Shader->UploadInt("u_Diffuse", ERenderingMapSlot::Diffuse);
		//}
	}

	void Material::SetViewProjection(const mat4& mat)
	{
		m_Shader->UploadUniformMat4("u_ViewProjection", mat);
	}

//	void Material::SetDiffuseMap(Texture2D* DiffuseMap)
//	{
//		//m_diffuseMap = DiffuseMap;
//	}
}

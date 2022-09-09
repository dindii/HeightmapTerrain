#pragma once
#include <string>
#include <Resources/Shader.h>
#include <Resources/Texture2D.h>
namespace Height
{
	class Material
	{
	public:
		//The idea here is an interface for Shader, to easily tweak some attributes and exclude de necessity of 
		//having shaders all over the place
		Material(const std::string& vertexpath, const std::string& fragpath);
		Material(Shader* shader) : m_Shader(shader) {};
		~Material();

		void Bind() const;
		inline Shader* GetShader() const { return m_Shader; }

		void SetViewProjection(const mat4& mat);

		//void SetDiffuseMap(Texture2D* DiffuseMap);
	private:
		Shader* m_Shader;

		//I will not implement this but I will keep this as an idea.
		//Texture2D* m_diffuseMap = nullptr;
	};
}
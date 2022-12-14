#pragma once
#include <string>
#include <Resources/Shader.h>
#include <Rendering/Renderer.h>

namespace Height
{

class FocalLight;
class Texture2D;

	class Material
	{
	public:
		//The idea here is an interface for Shader, to easily tweak some attributes and exclude the necessity of 
		//having shaders all over the place
		Material(const std::string& vertexpath, const std::string& fragpath);
		Material(Shader* shader) : m_Shader(shader) {};
		~Material();

		void Bind() const;
		inline Shader* GetShader() const { return m_Shader; }

		void SetViewProjection(const mat4& mat);
		void SetLightContext(const FocalLight* light);
		void SetCameraPos(const vec3& camPos);
		void AttachMap(Texture2D* map, EMapType mapType);
		
		void ToggleAttenuation(bool toggle);
	private:
		Shader* m_Shader;
		Texture2D* m_diffuseMap = nullptr;
	};
}
#pragma once
#include "Math/mat4.h"
#include <string>

namespace Height
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		Shader(const Shader& other) { *this = other; }
		Shader() = default;
		virtual ~Shader();

		virtual void Init(const std::string& vertexSource, const std::string& fragmentSource);

		virtual void Bind();
		virtual void UnBind();
		virtual void UploadUniformMat4(const std::string& name, const mat4& mat);
		virtual void UploadUniformFloat4(const std::string& name, const vec4& mat);
		virtual void UploadIntArray(const std::string& name, int* data, uint32_t count);
		virtual void UploadInt(const std::string& name, uint32_t data);

		uint32_t GetID() const { return m_RendererID; }

		void operator=(const Shader& other) { m_RendererID = other.GetID(); }
	private:
		virtual void ParseShaderFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		virtual void CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		virtual unsigned int CompileShader(unsigned int type, const std::string& source);

	private:
		uint32_t m_RendererID;
	};
}
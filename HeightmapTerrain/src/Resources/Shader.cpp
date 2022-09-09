#include "Shader.h"
#include <glad/glad.h>
#include "Util/HAssert.h"

#include <fstream>
#include <sstream>

namespace Height
{
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		Init(vertexSource, fragmentSource);
	}

	void Shader::Init(const std::string& vertexSource, const std::string& fragmentSource)
	{
		ParseShaderFiles(vertexSource, fragmentSource);
	}

	void Shader::ParseShaderFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::ifstream vertexShader, fragmentShader;

		vertexShader.open(vertexShaderPath);
		fragmentShader.open(fragmentShaderPath);

		HT_ASSERT((vertexShader && fragmentShader),"ERROR READING SHADER FILES!");
		
		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexShader.rdbuf();
		fragmentShaderStream << fragmentShader.rdbuf();

		vertexShader.close();
		fragmentShader.close();

		CreateShader(vertexShaderStream.str(), fragmentShaderStream.str());
	}

	void Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		//@TODO: DETTACH
		m_RendererID = program;

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int shaderId = glCreateShader(type);
		const char* src = source.c_str();

		glShaderSource(shaderId, 1, &src, nullptr);
		glCompileShader(shaderId);

		int compileResult;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);

		if (!compileResult)
		{
			int length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);

			//#NOTE: I have to allocate a stack variable of a fixed size (128, 256 etc) just to test if it works.
			char* message = new char[length];
			glGetShaderInfoLog(shaderId, length, &length, message);

			//We will just be using a simple cerr here. Not a problem at all since the creation of shaders (specially it's errors) should not be a
			//real time repetitive operation.
			if (type == GL_FRAGMENT_SHADER)
				std::cerr << "Failed to compile Fragment Shader: " << message << std::endl;

			else if (type == GL_VERTEX_SHADER)
				std::cerr << "Failed to compile Vertex Shader: "   << message << std::endl;

			else if (type == GL_GEOMETRY_SHADER)
				std::cerr << "Failed to compile Geometry Shader: " << message << std::endl;

			glDeleteShader(shaderId);
			delete[] message;
			return 0;
		}

		return shaderId;
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}


	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const mat4& mat)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat.elements[0]);

	}

	void Shader::UploadUniformFloat4(const std::string& name, const vec4& mat)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniform4f(location, mat.x, mat.y, mat.z, mat.w);
	}

	void Shader::UploadIntArray(const std::string& name, int* data, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniform1iv(location, count, data);
	}

}
#include "Shader.h"
#include <glad/glad.h>
#include "Util/HAssert.h"

#include <fstream>
#include <sstream>

namespace Height
{
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& tesControlSource, const std::string& tesEvaluationSource)
	{
		ParseShaderFiles(vertexSource, fragmentSource, tesControlSource, tesEvaluationSource);
	}

	void Shader::ParseShaderFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& tesControlSource, const std::string& tesEvaluationSource)
	{
		bool usingTesselation = tesControlSource.size() && tesEvaluationSource.size();

		std::ifstream vertexShader, fragmentShader, tesControlShader, tesEvaluationShader;

		vertexShader.open(vertexShaderPath);
		fragmentShader.open(fragmentShaderPath);

		HT_ASSERT((vertexShader && fragmentShader),"ERROR READING SHADER FILES!");
		
		if (usingTesselation)
		{
			tesControlShader.open(tesControlSource);
			tesEvaluationShader.open(tesEvaluationSource);
		
			HT_ASSERT((tesControlShader && tesEvaluationShader), "ERROR READING TESSELATION SHADER FILES!");
		}

		
		std::stringstream vertexShaderStream, fragmentShaderStream, tesControlShaderStream, tesEvaluationShaderStream;

		vertexShaderStream << vertexShader.rdbuf();
		fragmentShaderStream << fragmentShader.rdbuf();

		vertexShader.close();
		fragmentShader.close();
		
		if (usingTesselation)
		{
			tesControlShaderStream	  << tesControlShader.rdbuf();
			tesEvaluationShaderStream << tesEvaluationShader.rdbuf();
			
			tesControlShader.close();
			tesEvaluationShader.close();
		}

		CreateShader(vertexShaderStream.str(), fragmentShaderStream.str(), tesControlShaderStream.str(), tesEvaluationShaderStream.str());
	}

	void Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, const std::string& tesControlSource, const std::string& tesEvaluationSource)
	{
		bool usingTesselation = tesControlSource.size() && tesEvaluationSource.size();

		unsigned int program = glCreateProgram();
		
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		unsigned int tcs = 0;
		unsigned int tes = 0;

		glAttachShader(program, vs);
		glAttachShader(program, fs);

		if (usingTesselation)
		{
			tcs = CompileShader(GL_TESS_CONTROL_SHADER, tesControlSource);
			tes = CompileShader(GL_TESS_EVALUATION_SHADER, tesEvaluationSource);

			glAttachShader(program, tcs);
			glAttachShader(program, tes);
		}

		glLinkProgram(program);
		glValidateProgram(program);

		//@TODO: DETTACH
		m_RendererID = program;

		glDeleteShader(vs);
		glDeleteShader(fs);

		if(usingTesselation)
		{ 
			glDeleteShader(tcs);
			glDeleteShader(tes);
		}

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

			constexpr uint16_t errorMessageLength = 512;
			char message[errorMessageLength];
			glGetShaderInfoLog(shaderId, length, &length, message);

			HT_ASSERT(length < errorMessageLength, "Please, raise up the shader compilation error message buffer.");

			switch (type)
			{
				case GL_VERTEX_SHADER:
				{
					std::cerr << "Failed to compile Vertex Shader: " << message << std::endl;
				} break;
			
				case GL_FRAGMENT_SHADER:
				{
					std::cerr << "Failed to compile Fragment Shader: " << message << std::endl;
				} break;

				case GL_TESS_CONTROL_SHADER:
				{
					std::cerr << "Failed to compile Tessellation Control Shader: " << message << std::endl;
				} break;

				case GL_TESS_EVALUATION_SHADER:
				{
					std::cerr << "Failed to compile Tessellation Evaluation Shader: " << message << std::endl;
				} break;
				
				case GL_GEOMETRY_SHADER:
				{
					std::cerr << "Failed to compile Geometry Shader: " << message << std::endl;
				} break;
			}

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

	void Shader::UploadUniformFloat3(const std::string& name, const vec3& vec)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniform3f(location, vec.x, vec.y, vec.z);
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

	void Shader::UploadInt(const std::string& name, uint32_t data)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str()); //@TODO: Cache those locations
		glUniform1i(location, data);
	}

}
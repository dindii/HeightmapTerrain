#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Util/HAssert.h>
#include <Core/Application.h>
#include <Platform/Window.h>
#include <Math/vec4.h>
#include <Math/vec3.h>
#include <Resources/Mesh.h>
#include <Light/FocalLight.h>

namespace Height
{
	//Only visible here
	static uint32_t s_GlobalVertexArrayObject = 0;
	static bool     s_Initialized = false;
	bool Renderer::m_LightAttenuation = false;
	bool Renderer::m_NormalView = false;

	void Renderer::Init()
	{
		HT_ASSERT(!s_Initialized, "You can't have more than once OpenGL instance!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		bool openglInitialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HT_ASSERT(openglInitialized, "Failed to initialize OpenGL!");
			
		Application* app = Application::GetInstance();

		uint32_t width  = app->GetWindow()->GetWidth();
		uint32_t height = app->GetWindow()->GetHeight();

		glGenVertexArrays(1, &s_GlobalVertexArrayObject);
		glBindVertexArray(s_GlobalVertexArrayObject);

		SetViewport(0, 0, width, height);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Back face culling.
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_MULTISAMPLE);

		s_Initialized = true;
	}

	void Renderer::Clear(const bool ColorBuffer /*= true*/, const bool DepthBuffer /*= true*/)
	{
		if (ColorBuffer)
			glClear(GL_COLOR_BUFFER_BIT);

		if (DepthBuffer)
			glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetClearColor(const vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::SetWireframeMode(ERenderMode mode)
	{
		switch (mode)
		{
			case ERenderMode::TRIANGLE:
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			} break;
			case ERenderMode::LINE:
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} break;

			case ERenderMode::POINT:
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			} break;
		}
	}

	void Renderer::Draw(Mesh* mesh, Camera* camera, FocalLight* light)
	{
		Application* app = Application::GetInstance();

		RenderingHandles meshHandles = mesh->GetRenderingHandles();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshHandles.indexBufferHandle);
		
		Material* material = mesh->GetMaterial();
		material->Bind();
		material->SetViewProjection(camera->GetProjection() * camera->GetViewMatrix());
		material->SetLightContext(light);
		material->SetCameraPos(camera->GetCameraPos());
		material->ToggleAttenuation(m_LightAttenuation);

		//This will not be part of the material but of the renderer itself, so it will not be set through a material.
		material->GetShader()->UploadInt("u_NormalView", m_NormalView);

		glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, 0);
	}

	void Renderer::ToggleLightAttenuation()
	{
		m_LightAttenuation = !m_LightAttenuation;
	}

	void Renderer::ToggleNormalView()
	{
		m_NormalView = !m_NormalView;
	}

	uint32_t Renderer::GenResourceHandle()
	{
		unsigned int vertexBufferHandle = 0;
		glGenBuffers(1, &vertexBufferHandle);

		return vertexBufferHandle;
	}

	uint32_t Renderer::GenIndexHandle()
	{
		uint32_t returnIndexBuffer = 0;
		
		glGenBuffers(1, &returnIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, returnIndexBuffer);
		
		return returnIndexBuffer;
	}

	void Renderer::BindTexture(uint32_t textureHandle, EMapType type)
	{
		glBindTextureUnit(type, textureHandle);
	}

	void Renderer::RegisterData(const RenderingHandles& handle, const std::vector<vec3>& vertexPositions, const std::vector<uint32_t>& indices, const std::vector<vec2>& texCoords, const std::vector<vec3>& vertexNormals)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle.indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, handle.vertexBufferHandle);

		size_t bufferSize = sizeof(vec3) * vertexPositions.size() + sizeof(vec3) * vertexNormals.size() + sizeof(vec2) * texCoords.size();

		glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);

		//Upload buffer data in sequence. We do in the style of "XXXXXXXYYYYYYYYZZZZZZ" instead of "XYZXYZXYZ"
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * vertexPositions.size(), vertexPositions.data());
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec3) * vertexPositions.size(), (sizeof(vec3) * vertexNormals.size()), vertexNormals.data());
		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(vec3) * vertexPositions.size()) + (sizeof(vec3) * vertexNormals.size()), (sizeof(vec2) * texCoords.size()), texCoords.data());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Set the stride
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(vec3) * vertexPositions.size()));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)((sizeof(vec3) * vertexPositions.size()) + (sizeof(vec3) * vertexNormals.size())));
	}

	uint32_t Renderer::RegisterTextureResource(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels)
	{
		GLenum internalFormat = 0, dataFormat = 0;

		uint32_t m_RendererID = 0;

		switch (channels)
		{
			case 1:
			{
				internalFormat = GL_R8;
				dataFormat = GL_RED;
				break;
			}
			case 3:
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			}
			case 4:
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;
			}
			default:
			{
				std::cerr << "Unknown texture format type!" << std::endl;
				return 0;
			}
		}

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);

		if (channels == 1)
		{
			// Parameters to avoid ImGui messing up grayscale textures.	
			// This will make sure that the ImGui's shader can output
			// Color(val, val, val, 1.0) instead of Color(1.0, 0.0, 0.0, 1.0).
			glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_R, GL_RED);
			glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_G, GL_RED);
			glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_B, GL_RED);
			glTextureParameteri(m_RendererID, GL_TEXTURE_SWIZZLE_A, GL_ONE);
		}

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//This will give support to every dimension, even those that aren't even.
		if (!((width % 2) == 0))
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


		//This will give the user the freedom to start a blank texture so he can fill it later on.
		//The only requisite is to pre-config the texture with width, height and channels to make sure it's valid
		//If stbi could not load the image, we will catch this error in the switch above since we won't have any channel set.
		if (data)
		{
			glTextureSubImage2D(m_RendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		return m_RendererID;
		
	}

}
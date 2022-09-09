#include "Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Util/HAssert.h>
#include <Core/Application.h>
#include <Platform/Window.h>
#include <Math/vec4.h>
#include <Math/vec3.h>
#include <Resources/Mesh.h>


namespace Height
{
	//Only visible here
	static uint32_t s_GlobalVertexArrayObject = 0;
	static bool     s_Initialized = false;

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

	void Renderer::SetWireframeMode(bool cond)
	{
		if (cond)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Renderer::Draw(Mesh* mesh, Camera* camera)
	{
		Application* app = Application::GetInstance();

		glBindBuffer(GL_ARRAY_BUFFER, mesh->GetHandle());

		Material* material = mesh->GetMaterial();
		material->Bind();
		material->SetViewProjection(camera->GetProjection() * camera->GetViewMatrix());

		//#TODO: Please, let's use elements to draw.
		glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertexCount());
	}

	uint32_t Renderer::GenResourceHandle()
	{
		unsigned int vertexBufferHandle = 0;
		glGenBuffers(1, &vertexBufferHandle);

		return vertexBufferHandle;
	}

	void Renderer::RegisterData(const uint32_t objectHandleToUploadData, const std::vector<vec3>& vertexPositions)
	{
		glBindBuffer(GL_ARRAY_BUFFER, objectHandleToUploadData);

		size_t bufferSize = sizeof(vec3) * vertexPositions.size();

		glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * vertexPositions.size(), vertexPositions.data());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	}

}
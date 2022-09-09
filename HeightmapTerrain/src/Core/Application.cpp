#include "Application.h"

#include <Util/AppDefines.h>
#include <Util/HAssert.h>
#include <Util/DeltaTime.h>

#include <Event/Event.h>
#include <Platform/Window.h>
#include <Rendering/Renderer.h>
#include <Math/vec4.h>

namespace Height
{
	Application* Application::s_Instance = nullptr;

	Application::Application(float windowWidth, float windowHeight, const char* appName) : m_AppRunning(true)
	{
		HT_ASSERT(!s_Instance, "More than one instance of Application is not allowed.");

		s_Instance = this;

		m_ApplicationWindow = new Window(windowWidth, windowHeight, appName);
		m_ApplicationWindow->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		Renderer::SetClearColor(vec4(0.671, 0.131, 0.197, 1.0f));

		m_AppCamera = Camera(m_ApplicationWindow->GetAspectRatio(), { 0.0f, 0.0f, 1.0f });
		m_AppCamera.SetCameraLag(true);
		m_AppCamera.SetCameraLagValue(0.15f);

	////////ABSTRACT
		std::vector<vec3> triangleVertex;
		triangleVertex.push_back({-0.5f, -0.5f, 0.0f});
		triangleVertex.push_back({0.5f, -0.5f, 0.0f});
		triangleVertex.push_back({0.0f, 0.5f, 0.0f});

		m_TerrainMesh = new Mesh();
		m_TerrainMesh->SetVertexPositionData(std::move(triangleVertex));
		
		m_TerrainMeshMaterial = new Material("res/HeightmapVertexShader.shader","res/HeightmapFragmentShader.shader");

		m_TerrainMesh->AttachMaterial(m_TerrainMeshMaterial);
	}

	Application::~Application()
	{
		delete m_ApplicationWindow;
	}

	void Application::Run()
	{
		while (m_AppRunning)
		{
			m_DeltaTime.Tick();
			
			m_ApplicationWindow->OnUpdate();
			
			OnUpdate(m_DeltaTime);
		}
	}

	void Application::OnUpdate(const DeltaTime& dt)
	{
		Renderer::Clear();
		Renderer::Draw(m_TerrainMesh, &m_AppCamera);
	}

	void Application::OnEvent(Event& e)
	{
		//Do stuff
	}

}
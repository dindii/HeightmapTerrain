#include "Application.h"

#include <Util/AppDefines.h>
#include <Util/HAssert.h>
#include <Util/DeltaTime.h>

#include <Event/Event.h>
#include <Event/ApplicationEvent.h>
#include <Event/KeyEvent.h>

#include <Platform/Window.h>
#include <Rendering/Renderer.h>
#include <Math/vec4.h>

#include <Terrain/TerrainMesh.h>
#include <Input/Input.h>
#include <Math/GeneralMath.h>

namespace Height
{
	Application* Application::s_Instance = nullptr;

	Application::Application(float windowWidth, float windowHeight, const char* appName) : m_AppRunning(true), m_MouseLockedAndInvisible(true), m_DefaultCameraSpeed(50.0f),
		m_TerrainDiffuseMap(nullptr)
	{
		HT_ASSERT(!s_Instance, "More than one instance of Application is not allowed.");

		s_Instance = this;

		m_ApplicationWindow = new Window(windowWidth, windowHeight, appName);
		m_ApplicationWindow->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		Renderer::SetClearColor(vec4(0.5f, 0.5f, 0.5f, 1.0f));

		m_AppCamera = Camera(m_ApplicationWindow->GetAspectRatio(), { 0.0f, 0.0f, 1.0f });
		m_AppCamera.SetCameraLag(true);
		m_AppCamera.SetCameraLagValue(0.15f);

		m_Terrain = new TerrainMesh("res/perlinnoise.png", 64.0f, 16.0f);
		m_TerrainMaterial = new Material("res/HeightmapVertexShader.shader","res/HeightmapFragmentShader.shader");

		//m_TerrainDiffuseMap = new Texture2D("res/texturePlaceholder.png");
		//m_TerrainMaterial->AttachMap(m_TerrainDiffuseMap, EMapType::DIFFUSE_MAP);

		m_Terrain->AttachMaterial(m_TerrainMaterial);
	}

	Application::~Application()
	{
		delete m_Terrain;
		delete m_TerrainMaterial;

		if(m_TerrainDiffuseMap)
			delete m_TerrainDiffuseMap;

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

	void Application::OnUpdate(DeltaTime& dt)
	{
		Renderer::Clear();

		MoveCamera(dt);
		LookAround();

		Renderer::Draw(m_Terrain, &m_AppCamera);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizeEvent>([&](WindowResizeEvent Event) -> bool
		{
			Renderer::SetViewport(0, 0, Event.GetWidth(), Event.GetHeight());
			m_AppCamera.RemakeProjection((float)Event.GetWidth(), (float)Event.GetHeight());
			return true;
		});


		dispatcher.Dispatch<KeyPressedEvent>([&](KeyPressedEvent Event) -> bool
		{
			switch (Event.GetKeyCode())
			{
			case HT_KEY_ESCAPE:
			{
				TerminateApplication();
				return true;
			}   break;

			case HT_KEY_F2:
			{
				m_MouseLockedAndInvisible = !m_MouseLockedAndInvisible;

				Input::HideAndLockCursor(m_MouseLockedAndInvisible);
				m_AppCamera.LockCamera(!m_MouseLockedAndInvisible);

				return true;

			}   break;

			case HT_KEY_F3:
			{
				uint8_t fooEnum = (uint8_t)m_RenderMode;
				fooEnum++;
				fooEnum %= ERenderMode::END;
				m_RenderMode = (ERenderMode)fooEnum;

				Renderer::SetWireframeMode(m_RenderMode);
				return true;

			}   break;

			default:
				return false;
			}
		});
	}

	void Application::MoveCamera(DeltaTime& dt)
	{
		vec3 IntendedCameraPosition;

		if (Input::IsKeyPressed(EKeyCode::HT_KEY_W))
			IntendedCameraPosition.z = -m_DefaultCameraSpeed;

		if (Input::IsKeyPressed(EKeyCode::HT_KEY_S))
			IntendedCameraPosition.z = m_DefaultCameraSpeed;

		if (Input::IsKeyPressed(EKeyCode::HT_KEY_D))
			IntendedCameraPosition.x = m_DefaultCameraSpeed;

		if (Input::IsKeyPressed(EKeyCode::HT_KEY_A))
			IntendedCameraPosition.x = -m_DefaultCameraSpeed;

		if (Input::IsKeyPressed(EKeyCode::HT_KEY_SPACE))
			IntendedCameraPosition.y = m_DefaultCameraSpeed;

		if (Input::IsKeyPressed(EKeyCode::HT_KEY_LEFT_CONTROL))
			IntendedCameraPosition.y = -m_DefaultCameraSpeed;

		//Add this vector on the Target Position (a.k.a eye position), this is, where we are looking at, thus making a free camera style
		m_AppCamera.AddCameraTargetPosition(IntendedCameraPosition, dt);
	}

	void Application::LookAround()
	{
		vec2 MousePosition = Input::GetMousePosition();

		m_AppCamera.SetCameraYaw(  toRadians(MousePosition.x));
		m_AppCamera.SetCameraPitch(toRadians(MousePosition.y));
	}

	void Application::TerminateApplication()
	{
		m_AppRunning = false;
	}

}
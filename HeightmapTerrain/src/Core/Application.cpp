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

	Application::Application(float windowWidth, float windowHeight, const char* appName, std::string heightmapTexture, std::string diffuseTexture)
		: m_AppRunning(true), m_MouseLockedAndInvisible(true), m_DefaultCameraSpeed(50.0f), m_TerrainDiffuseMap(nullptr), m_DefaultLightSpeed(40.0f)
	{
		HT_ASSERT(!s_Instance, "More than one instance of Application is not allowed.");

		//Our App class is a singleton
		s_Instance = this;

		//Window creation
		m_ApplicationWindow = new Window(windowWidth, windowHeight, appName);
		
		//For this program, we don't need a very complex event system with observers. I will just get the events from the window (this is, input, resize etc) and receive them on the OnEvent app function
		//from there, I will distribute it to the other app systems.
		//I use BIND_EVENT_FN as a std::bind, so we don't need to pass the address of the app object.
		m_ApplicationWindow->setEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		Renderer::SetClearColor(vec4(0.5f, 0.5f, 0.5f, 1.0f));

		m_AppCamera = Camera(m_ApplicationWindow->GetAspectRatio(), { 0.0f, 0.0f, 1.0f });
		
		//Camera lag is basically the smoothness of the camera movement, basically a lerp.
		m_AppCamera.SetCameraLag(true);
		m_AppCamera.SetCameraLagValue(0.15f);

		//We allocate the mesh because we are not sure about the size of the terrain. But this could be allocated on the stack (since its members are allocated in the heap anyway).
		//I do prefer doing this in this small project because I want to have more control.
		m_Terrain = new TerrainMesh(heightmapTexture, 64.0f, 16.0f);
		
		//And we allocate a material because this is an asset. This is meant to be reused a lot. In this small project, we just delete it after the app ends, but in a bigger project
		//we usually have a asset manager that maps this asset to a shared pointer and retrieve this pointer when we try to load the same asset. So a lot of meshes can share the same material and have the same
		//visual behavior.
		m_TerrainMaterial = new Material("res/HeightmapVertexShader.shader","res/HeightmapFragmentShader.shader");

		//This is optional, but Materials make use of Textures as well. Texture is usually a shared asset.
		if (diffuseTexture.size() > 0)
		{
			m_TerrainDiffuseMap = new Texture2D(diffuseTexture);
			m_TerrainMaterial->AttachMap(m_TerrainDiffuseMap, EMapType::DIFFUSE_MAP);
		}

		//Since the Material is an asset, we have multiple materials and set multiple different materials to the same mesh (as well as reutilize the material for other meshes)
		m_Terrain->AttachMaterial(m_TerrainMaterial);

		//Arbitrary pos
		m_TerrainLight.SetPosition({ 0.0f, 30.0f, 0.0f });
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
			
			//Update platform Window important stuff, like input polling and swap chain
			m_ApplicationWindow->OnUpdate();
			
			OnUpdate(m_DeltaTime);
		}
	}

	void Application::OnUpdate(DeltaTime& dt)
	{
		Renderer::Clear();

		LookAround();
		MoveCamera(dt);
		MoveLight(dt);

		Renderer::Draw(m_Terrain, &m_AppCamera, &m_TerrainLight);
	}

	void Application::OnEvent(Event& e)
	{
		//Here, we basically feed the EventDispatcher with an event and it will check the event type. If the event type is the same as the type of the Dispatch<>() function, it will call the appropriate callback
		//and pass the corresponding event as the parameter. To keep the code kinda short, it just used lambdas, but we could just bind any functions to it as a callback.
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
				//Make mouse invisible and make it locked inside the screen
				m_MouseLockedAndInvisible = !m_MouseLockedAndInvisible;

				Input::HideAndLockCursor(m_MouseLockedAndInvisible);
				m_AppCamera.LockCamera(!m_MouseLockedAndInvisible);

				return true;

			}   break;

			case HT_KEY_F3:
			{
				//Make a selector that loops between all render modes
				uint8_t fooEnum = (uint8_t)m_RenderMode;
				fooEnum++;
				fooEnum %= ERenderMode::END;
				m_RenderMode = (ERenderMode)fooEnum;

				Renderer::SetWireframeMode(m_RenderMode);
				return true;

			}   break;

			case HT_KEY_F4:
			{
				Renderer::ToggleLightAttenuation();
				return true;
			} break;
			
			case HT_KEY_F5:
			{
				//Render only the normals
				Renderer::ToggleNormalView();
				return true;
			} break;

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

	void Application::MoveLight(DeltaTime& dt)
	{
		vec3 LightPos;

		if (Input::IsKeyPressed(EKeyCode::HT_KEY_RIGHT_SHIFT))
			LightPos.y += m_DefaultLightSpeed;
		
		if (Input::IsKeyPressed(EKeyCode::HT_KEY_RIGHT_CONTROL))
			LightPos.y += -m_DefaultLightSpeed;

		LightPos.x += cos(m_ApplicationWindow->GetTime()) * 1000.0f;
		LightPos.z += sin(m_ApplicationWindow->GetTime()) * 1000.0f;

		m_TerrainLight.AddPosition(LightPos * dt);

		m_TerrainLight.SetPosition(m_AppCamera.GetCameraPos());
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
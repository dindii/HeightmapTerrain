#pragma once

#include <Util/DeltaTime.h>
#include <Resources/Mesh.h>
#include <Visual/Material.h>
#include <Camera/Camera.h>
#include <Rendering/Renderer.h>

namespace Height
{

class Event;
class Window;
class TerrainMesh;

class Application
	{
	public:
		Application(float windowWidth, float windowHeight, const char* appName);
		virtual ~Application();

		void Run();
		void OnUpdate(DeltaTime& dt);

		void OnEvent(Event& e);
		static Application* GetInstance() { return s_Instance; }
		inline Window* GetWindow() { return m_ApplicationWindow; }

		void TerminateApplication();

	private:
		static Application* s_Instance;
		Window* m_ApplicationWindow;
		DeltaTime m_DeltaTime;

		bool m_AppRunning;

		//Our project specific resources
	private:
		void MoveCamera(DeltaTime& dt);
		void LookAround();
		
		Camera   m_AppCamera;
		TerrainMesh*     m_Terrain;
		Material* m_TerrainMaterial;
		Texture2D* m_TerrainDiffuseMap;
		bool m_MouseLockedAndInvisible;
		ERenderMode m_RenderMode;
		float m_DefaultCameraSpeed;
	};
}
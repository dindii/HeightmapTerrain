#pragma once

#include <Util/DeltaTime.h>
#include <Resources/Mesh.h>
#include <Visual/Material.h>
#include <Camera/Camera.h>

namespace Height
{

class Event;
class Window;

class Application
	{
	public:
		Application(float windowWidth, float windowHeight, const char* appName);
		virtual ~Application();

		void Run();
		void OnUpdate(const DeltaTime& dt);

		void OnEvent(Event& e);
		static Application* GetInstance() { return s_Instance; }
		inline Window* GetWindow() { return m_ApplicationWindow; }

	private:
		static Application* s_Instance;
		Window* m_ApplicationWindow;
		DeltaTime m_DeltaTime;

		bool m_AppRunning;

		//Our project specific resources
	private:
		Camera   m_AppCamera;
		Mesh*     m_TerrainMesh;
		Material* m_TerrainMeshMaterial;
	};
}
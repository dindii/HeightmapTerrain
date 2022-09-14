#pragma once

#include <Util/DeltaTime.h>
#include <Resources/Mesh.h>
#include <Visual/Material.h>
#include <Camera/Camera.h>
#include <Rendering/Renderer.h>
#include <Light/FocalLight.h>

namespace Height
{

class Event;
class Window;
class TerrainMesh;

class Application
	{
	public:
		Application(float windowWidth, float windowHeight, const char* appName, std::string heightmapTexture, std::string diffuseTexture = std::string());
		virtual ~Application();

		//main app loop
		void Run();

		//Update all systems
		void OnUpdate(DeltaTime& dt);

		//Flows all events down to all systems
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
		//Usually we don't have more than one entity to move via input, but in this case we will have.
		void MoveCamera(DeltaTime& dt);
		void MoveLight (DeltaTime& dt);

		void LookAround();
		
		//Light that will walk above the terrain
		FocalLight m_TerrainLight;

		//App camera
		Camera   m_AppCamera;

		//Our generated mesh
		TerrainMesh*     m_Terrain;

		//Our material. A material is a combination of shaders, uniforms and textures.
		//This is usually an asset, you can assign a material to whatever mesh you want.
		Material* m_TerrainMaterial;

		//Our optional texture
		Texture2D* m_TerrainDiffuseMap;

		//Hide mouse bool
		bool m_MouseLockedAndInvisible;

		//Render mode (wireframe, opaque, points etc...)
		ERenderMode m_RenderMode;

		float m_DefaultCameraSpeed;
		float m_DefaultLightSpeed;
	};
}
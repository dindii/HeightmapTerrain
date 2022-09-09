#include "DeltaTime.h"
#include <Core/Application.h>
#include <Platform/Window.h>

namespace Height
{
	void DeltaTime::Tick()
	{
		Application* app = Application::GetInstance();

		currentTime = app->GetWindow()->GetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
	}
}
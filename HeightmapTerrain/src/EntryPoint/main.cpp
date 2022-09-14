#include <Core/Application.h>

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		Height::Application app(800, 450, "Height map Terrain Renderer!", argv[1], argv[2]);
		app.Run();
	}
	else
	{
		Height::Application app(800, 450, "Height map Terrain Renderer!", argv[1]);
		app.Run();
	}
	

	return 0;
}
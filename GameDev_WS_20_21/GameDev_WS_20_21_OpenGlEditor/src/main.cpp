#include "Engine.h"

#include "Rendering/Display.h"

int main()
{
	Engine::Init();

	while (!glfwWindowShouldClose(Display::GetWindow()))
	{
		Engine::Update();
	}
	

	Engine::ShutDown();
	return 0;
}

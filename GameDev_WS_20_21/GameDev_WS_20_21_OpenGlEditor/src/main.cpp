#include "EditorManager.h"
#include "Engine.h"
#include "UiManager.h"

#include "Rendering/Display.h"

int main()
{
	Engine::Init();
	UiManager::Init();

	EditorManager::InitDefaultScene();
	
	while (!glfwWindowShouldClose(Display::GetWindow()))
	{
		Engine::Update();
	}
	
	UiManager::ShutDown();
	Engine::ShutDown();
	return 0;
}

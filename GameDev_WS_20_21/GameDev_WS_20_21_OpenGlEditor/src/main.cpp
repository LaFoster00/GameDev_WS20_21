#include "Engine.h"
#include "UiManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Camera.h"
#include "GameSystems/GameManager.h"

#include "Rendering/Display.h"

int main()
{
	Engine::Init();
	UiManager::Init();

	//setup basic needed objects for editor to work correctly
	GameObject* mainCamera = GameManager::AddGameObject("Camera", glm::vec3(-2, 0, 0), glm::vec3(0, 0, 0));
	CameraRenderSettings cameraSettings;
	cameraSettings.fov = 90;
	Camera* camera = new Camera(cameraSettings);
	mainCamera->AddComponent(camera);
	
	while (!glfwWindowShouldClose(Display::GetWindow()))
	{
		
		
		Engine::Update();
	}
	
	UiManager::ShutDown();
	Engine::ShutDown();
	return 0;
}

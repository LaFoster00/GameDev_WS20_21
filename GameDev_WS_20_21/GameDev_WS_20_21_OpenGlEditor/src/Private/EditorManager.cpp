#include "EditorManager.h"


#include "GameObjects/Components/Camera.h"
#include "GameSystems/GameManager.h"

Scene* EditorManager::CurrentlyOpenScene;

void EditorManager::InitDefaultScene()
{
	//setup basic needed objects for editor to work correctly
	GameObject* mainCamera = GameManager::AddGameObject("Camera", glm::vec3(-2, 0, 0), glm::vec3(0, 0, 0));
	CameraRenderSettings cameraSettings;
	cameraSettings.fov = 90;
	Camera* camera = new Camera(cameraSettings);
	mainCamera->AddComponent(camera);

	CurrentlyOpenScene = new Scene();
	CurrentlyOpenScene->GameObjects.push_back(mainCamera);
}

void EditorManager::LoadScene(const std::string& filepath, bool saveCurrentScene)
{
	if (CurrentlyOpenScene)
	{
		if (saveCurrentScene)
		{
			SaveScene(CurrentlyOpenScene->Filepath);
		}
		
		for (auto sceneObject : CurrentlyOpenScene->GameObjects)
		{
			GameManager::DestroyGameObject(sceneObject);
		}
	}
}

void EditorManager::SaveScene(const std::string& filepath)
{
	CurrentlyOpenScene->Save(filepath);
}

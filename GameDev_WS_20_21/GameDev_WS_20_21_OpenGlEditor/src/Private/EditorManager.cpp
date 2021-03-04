#include "EditorManager.h"


#include "GameObjects/Components/Camera.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "GameObjects/Components/Transform.h"
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

	std::ifstream file(filepath);
	if (file.is_open())
	{
		nlohmann::json saveFile = nlohmann::json::parse(file);
		CurrentlyOpenScene->Name = saveFile["SceneName"];
		CurrentlyOpenScene->Filepath = filepath;

		std::vector<nlohmann::json> gameObjects = saveFile["GameObjects"].get<std::vector<nlohmann::json>>();

		for (auto gameObject: saveFile["GameObjects"].items())
		{
			GameObject* newGameObject = new GameObject(gameObject.key(), glm::vec3(0), glm::vec3(0));
			GameManager::AddGameObject(newGameObject);
			CurrentlyOpenScene->GameObjects.push_back(newGameObject);
			
			for (auto component: gameObject.value()["Components"].items())
			{
				nlohmann::ordered_json componentJson = component.value();
				if (component.key() == typeid(Camera).name())
				{
					Camera* camera = new Camera(componentJson);
					newGameObject->AddComponent(camera);
				}
				else if (component.key() == typeid(MeshRenderer).name())
				{	
					MeshRenderer* meshRenderer = new MeshRenderer(componentJson);
					newGameObject->AddComponent(meshRenderer);
				}
				else if (component.key() == typeid(Transform).name())
				{
					Transform* newTransform = new Transform(componentJson);
					newGameObject->AddComponent(newTransform);
				}
			}
		}
	}
}

void EditorManager::SaveScene(const std::string& filepath)
{
	CurrentlyOpenScene->Save(filepath);
}
#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "GameObjects/GameObject.h"
#include "GameSystems/GameManager.h"

class GameObject;

struct Scene
{
	std::string Name = "Scene";
	std::string Filepath = "None";

	void Save(const std::string& filepath)
	{
		nlohmann::ordered_json saveFile;
		saveFile["SceneName"] = Name;

		std::vector<nlohmann::ordered_json> gameObjects;
		for (auto object : GameManager::GetGameObjects())
		{
			gameObjects.push_back(object->Serialize());
		}

		saveFile["GameObjects"] = gameObjects;
		
		std::ofstream file(filepath);
		file << saveFile.dump(4);
		file.close();
	}

	const void Clear()
	{
		GameManager::Clear();
	}
};

class EditorManager
{
public:
	static void InitDefaultScene();
	static void LoadScene(const std::string& filepath, bool saveCurrentScene = false);
	static void SaveScene(const std::string& filepath);

	static void UpdateSceneOutliner();
public:
	static Scene* CurrentlyOpenScene;
	static GameObject* SelectedGameObject;
	static std::vector<std::string> OutlinerNames;

private:
	static EngineCallback GameObjectNotify;
};
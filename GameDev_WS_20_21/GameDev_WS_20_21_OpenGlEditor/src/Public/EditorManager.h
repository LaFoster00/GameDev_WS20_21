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
	std::vector<GameObject*> GameObjects;

	std::string Filepath = "None";

	void Save(const std::string& filepath)
	{
		nlohmann::ordered_json saveFile;
		saveFile["SceneName"] = Name;

		std::vector<nlohmann::ordered_json> gameObjects;
		for (auto object : GameObjects)
		{
			gameObjects.push_back(object->Serialize());
		}

		saveFile["GameObjects"] = gameObjects;
		
		std::ofstream file(filepath);
		file << saveFile.dump(4);
		file.close();
	}

	void Clear()
	{
		for (auto sceneObject : GameObjects)
		{
			GameManager::DestroyGameObject(sceneObject);
		}

		GameObjects.clear();
	}
};

class EditorManager
{
public:
	static void InitDefaultScene();
	static void LoadScene(const std::string& filepath, bool saveCurrentScene = false);
	static void SaveScene(const std::string& filepath);

public:
	static Scene* CurrentlyOpenScene;
};
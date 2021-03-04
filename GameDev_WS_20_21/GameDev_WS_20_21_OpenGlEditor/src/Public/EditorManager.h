#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "GameObjects/GameObject.h"

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

		for (auto object : GameObjects)
		{
			object->Serialize(saveFile);
		}

		std::ofstream file(filepath);
		file << saveFile.dump(4);
		file.close();
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
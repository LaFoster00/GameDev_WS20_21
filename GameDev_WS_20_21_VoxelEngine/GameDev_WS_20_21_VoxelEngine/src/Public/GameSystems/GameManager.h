#pragma once
#include <string>
#include <vector>
#include <glm/vec3.hpp>

class GameObject;

class GameManager
{
public:
	GameManager();
	~GameManager();
	
	static GameObject* AddGameObject();
	static GameObject* AddGameObject(const std::string& name, glm::vec3 position, glm::vec3 rotation);
	static void AddGameObject(GameObject* gameObject);
	static void DestroyGameObject(GameObject* gameObject);

	static bool IsGameObjectInGame(GameObject* gameObject);
private:
	static std::vector<GameObject*> m_gameObjects;
};

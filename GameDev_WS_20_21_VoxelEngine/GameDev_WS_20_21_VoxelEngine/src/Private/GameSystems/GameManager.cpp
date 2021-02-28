#include "GameSystems/GameManager.h"

#include "GameObjects/GameObject.h"
#include "GameSystems/InputManager.h"

std::vector<GameObject*> GameManager::m_gameObjects;

GameManager::GameManager()
{
	InputManager::InitInput();
}

GameManager::~GameManager()
{
	if (m_gameObjects.size() > 0)
	{
		for (uint32_t i = m_gameObjects.size(); i > 0; i--)
		{
			delete m_gameObjects[i - 1];
		}
	}
}

GameObject* GameManager::AddGameObject()
{
	GameObject* gameObject = new GameObject();
	m_gameObjects.push_back(gameObject);

	return gameObject;
}

GameObject* GameManager::AddGameObject(const std::string& name, glm::vec3 position, glm::vec3 rotation)
{
	GameObject* gameObject = new GameObject(name, position, rotation);
	m_gameObjects.push_back(gameObject);

	return gameObject;
}

void GameManager::AddGameObject(GameObject* gameObject)
{
	if (std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject) != m_gameObjects.end())
	{
		std::cout << "This gameObject is already part of the game!" << std::endl;
		return;
	}
	
	m_gameObjects.push_back(gameObject);
}

void GameManager::DestroyGameObject(GameObject* gameObject)
{
	auto index = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
	if (index == m_gameObjects.end())
	{
		std::cout << "This gameObject isn't part of the game or not valid anymore!" << std::endl;
		return;
	}

	delete gameObject;
	m_gameObjects.erase(index);
}

bool GameManager::IsGameObjectInGame(GameObject* gameObject)
{
	return std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject) != m_gameObjects.end();
}

#include "GameSystems/GameManager.h"

#include <iostream>

#include "GameObjects/GameObject.h"
#include "GameSystems/InputManager.h"
#include "GameSystems/Callbacks.h"


std::vector<GameObject*> GameManager::m_gameObjects;
std::unordered_map<uint32_t, EngineCallback*> GameManager::GameObjectNotify;

std::unordered_map< uint32_t, EngineCallback*> GameManager::UpdateCallbacks;
std::unordered_map< uint32_t, EngineCallback*> GameManager::EngineShutDownCallbacks;

void GameManager::Init()
{
	InputManager::InitInput();
}

void GameManager::ShutDown()
{
	if (m_gameObjects.size() > 0)
	{
		for (size_t i = m_gameObjects.size(); i > 0; i--)
		{
			delete m_gameObjects[i - 1];
		}
	}

	for (auto shutDownCallback : EngineShutDownCallbacks)
	{
		shutDownCallback.second->callback();
	}
}

void GameManager::Update()
{
	for (auto updateCallback : UpdateCallbacks)
	{
		updateCallback.second->callback();
	}
}

void GameManager::AddUpdateCallback(EngineCallback& callback)
{
	if (UpdateCallbacks.find(callback.id) == UpdateCallbacks.end())
	{
		UpdateCallbacks[callback.id] = &callback;
	}
}

void GameManager::RemoveUpdateCallback(EngineCallback& callback)
{
	if (UpdateCallbacks.find(callback.id) != UpdateCallbacks.end())
	{
		UpdateCallbacks.erase(callback.id);
	}
}

void GameManager::AddEngineShutDownCallback(EngineCallback& callback)
{
	if (EngineShutDownCallbacks.find(callback.id) == EngineShutDownCallbacks.end())
	{
		EngineShutDownCallbacks[callback.id] = &callback;
	}
}

void GameManager::RemoveEngineShutDownCallback(EngineCallback& callback)
{
	if (EngineShutDownCallbacks.find(callback.id) != EngineShutDownCallbacks.end())
	{
		EngineShutDownCallbacks.erase(callback.id);
	}
}

void GameManager::AddGameObjectNotifyCallback(EngineCallback& callback)
{
	if (GameObjectNotify.find(callback.id) == GameObjectNotify.end())
	{
		GameObjectNotify[callback.id] = &callback;
	}
}

void GameManager::RemoveGameObjectNotifyCallback(EngineCallback& callback)
{
	if (GameObjectNotify.find(callback.id) != GameObjectNotify.end())
	{
		GameObjectNotify.erase(callback.id);
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
	if (IsGameObjectInGame(gameObject))
	{
		std::cout << "This gameObject is already part of the game!" << std::endl;
		return;
	}
	
	m_gameObjects.push_back(gameObject);

	for (auto notifyCallback : GameObjectNotify)
	{
		notifyCallback.second->callback();
	}
}

void GameManager::DestroyGameObject(GameObject* gameObject)
{
	if (!IsGameObjectInGame(gameObject))
	{
		std::cout << "This gameObject isn't part of the game or not valid anymore!" << std::endl;
		return;
	}

	auto index = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
	delete gameObject;
	m_gameObjects.erase(index);

	for (auto notifyCallback : GameObjectNotify)
	{
		notifyCallback.second->callback();
	}
}

void GameManager::Clear()
{
	for (auto object : m_gameObjects)
	{
		delete object;
	}

	m_gameObjects.clear();

	for (auto notifyCallback : GameObjectNotify)
	{
		notifyCallback.second->callback();
	}
}

bool GameManager::IsGameObjectInGame(GameObject* gameObject)
{
	return std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject) != m_gameObjects.end();
}

std::vector<GameObject*>& GameManager::GetGameObjects()
{
	return m_gameObjects;
}

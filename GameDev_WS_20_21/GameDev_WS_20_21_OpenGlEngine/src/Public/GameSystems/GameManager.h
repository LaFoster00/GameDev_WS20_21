#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <glm/vec3.hpp>

struct EngineCallback;
class GameObject;

class GameManager
{
public:
	static void Init();
	static void ShutDown();
	static void Update();
	
	static void AddUpdateCallback(EngineCallback& callback);
	static void RemoveUpdateCallback(EngineCallback& callback);

	static void AddEngineShutDownCallback(EngineCallback& callback);
	static void RemoveEngineShutDownCallback(EngineCallback& callback);
	
	//GameObject handling
	static GameObject* AddGameObject();
	static GameObject* AddGameObject(const std::string& name, glm::vec3 position, glm::vec3 rotation);
	static void AddGameObject(GameObject* gameObject);
	static void DestroyGameObject(GameObject* gameObject);

	static bool IsGameObjectInGame(GameObject* gameObject);
private:
	static std::vector<GameObject*> m_gameObjects;

	static std::unordered_map< uint32_t, EngineCallback*> UpdateCallbacks;
	static std::unordered_map< uint32_t, EngineCallback*> EngineShutDownCallbacks;
};
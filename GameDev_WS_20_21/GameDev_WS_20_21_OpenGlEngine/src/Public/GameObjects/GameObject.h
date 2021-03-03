#pragma once
#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>

class Component;

/// <summary>
/// Game Objects are inspired by Unity and hold a reference to all components that need to be associated
/// with one another
/// It will also clean up all components once it gets destroyed
/// </summary>
class GameObject
{
public:
	GameObject();
	GameObject(const std::string& name, glm::vec3 position, glm::vec3 rotation);
	~GameObject();

	virtual void Serialize(nlohmann::ordered_json& archive);
	
	template<typename T>
	bool AddComponent(T* tComponent)
	{
		Component* castComponent = dynamic_cast<Component*>(tComponent);
		castComponent->gameObject = this;

		size_t typeHash = typeid(T).hash_code();

		if (m_components.find(typeHash) != m_components.end())
		{
			return false;
		}

		m_components[typeHash] = castComponent;
		return true;
	}
	

	template<typename T>
	bool RemoveComponent(bool destroy = true)
	{
		size_t typeHash = typeid(T).hash_code();
		if (m_components.find(typeHash) == m_components.end())
		{
			return false;
		}

		if (destroy) delete m_components[typeHash];
		m_components.erase(typeHash);
	}

	template<typename T>
	T* GetComponentOfType()
	{
		size_t typeHash = typeid(T).hash_code();
		if (m_components.find(typeHash) == m_components.end())
		{
			return nullptr;
		}

		return dynamic_cast<T*>(m_components[typeHash]);
	}

public:
	uint32_t id;
	std::string internalName;
	std::string name;

private:
	std::unordered_map<size_t, Component*> m_components;

	uint32_t GetNewId();
};

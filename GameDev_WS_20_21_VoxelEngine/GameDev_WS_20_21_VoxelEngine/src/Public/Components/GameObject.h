#pragma once
#include <string>
#include <unordered_map>

#include "Component.h"

class Transform;

class GameObject
{
public:
	GameObject();
	GameObject(std::string& name, Transform* transform);
	~GameObject();
	
	template<typename T>
	bool AddComponent(T* Component);

	template<typename T>
	bool RemoveComponent(T* Component, bool destroy = true);

	template<typename T>
	T* GetComponentOfType();

public:
	uint32_t id;
	std::string internalName;
	std::string name;

private:
	std::unordered_map<size_t, Component*> m_components;

	uint32_t GetNewId();
};

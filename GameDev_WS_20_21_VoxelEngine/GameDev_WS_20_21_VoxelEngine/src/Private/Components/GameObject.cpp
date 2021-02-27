#include "Components/GameObject.h"

#include <vcruntime_typeinfo.h>

#include <utility>


#include "Components/Component.h"
#include "Components/Transform.h"

template <typename T>
bool GameObject::AddComponent(T* component)
{
	Component* castComponent = dynamic_cast<Component*>(component);
	size_t typeHash = typeid(T).hash_code();
	
	if (m_components.find(typeHash) != m_components.end())
	{
		return false;
	}
	
	m_components[typeHash] = component;
	return true;
}

template <typename T>
bool GameObject::RemoveComponent(T* Component, bool destroy)
{
	size_t typeHash = typeid(T).hash_code();
	if (m_components.find(typeHash) != m_components.end())
	{
		return false;
	}

	if (destroy) delete m_components[typeHash];
	m_components.erase(typeHash);
}

template <typename T>
T* GameObject::GetComponentOfType()
{
	size_t typeHash = typeid(T).hash_code();
	if (m_components.find(typeHash) != m_components.end())
	{
		return nullptr;
	}
	
	return reinterpret_cast<T*>(m_components[typeHash]);
}

GameObject::GameObject()
{
	id = GetNewId();
	internalName = "GameObject" + std::to_string(id);
	this->name = "GameObject";

	auto transform = new Transform();
	AddComponent(transform);
}

GameObject::GameObject(std::string& name, Transform* transform)
{
	id = GetNewId();
	internalName = "GameObject" + std::to_string(id);
	this->name = name;

	AddComponent(transform);
}

GameObject::~GameObject()
{
	for (auto m_component : m_components)
	{
		delete m_component.second;
	}
}


uint32_t GameObject::GetNewId()
{
	static uint32_t ID = 0;
	return id++;
}

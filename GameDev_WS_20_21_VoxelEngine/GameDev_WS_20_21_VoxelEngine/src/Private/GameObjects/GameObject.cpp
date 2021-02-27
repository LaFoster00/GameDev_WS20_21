#include "Components/GameObject.h"
#include "Components/Component.h"
#include "Components/Transform.h"

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

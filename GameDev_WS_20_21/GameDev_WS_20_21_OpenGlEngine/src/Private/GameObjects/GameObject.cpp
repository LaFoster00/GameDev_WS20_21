#include "GameObjects/GameObject.h"

#include "GameObjects/Components/Transform.h"
#include "Serialization/JsonArchive.h"

GameObject::GameObject()
{
	id = GetNewId();
	internalName = "GameObject" + std::to_string(id);
	this->name = "GameObject";

	Transform* transform = new Transform();
	AddComponent(transform);
}

GameObject::GameObject(const std::string& name, glm::vec3 position, glm::vec3 rotation)
{
	id = GetNewId();
	internalName = "GameObject" + std::to_string(id);
	this->name = name;

	Transform* transform = new Transform(position, glm::vec3(1), rotation);
	AddComponent(transform);
}

GameObject::~GameObject()
{
	for (auto m_component : m_components)
	{
		delete m_component.second;
	}
}

void GameObject::Serialize(nlohmann::ordered_json& archive)
{
	for (auto component : m_components)
	{
		archive["GameObjects"][name]["Components"][typeid(component.second).raw_name()] = component.second->Serialize();
	}
}


uint32_t GameObject::GetNewId()
{
	static uint32_t ID = 0;
	return id++;
}
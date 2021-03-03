#include "GameObjects/Components/Component.h"

#include <iostream>

#include "GameSystems/GameManager.h"

Component::Component(bool CallUpdate) :
	updateCallback([this]() { Update(); })
{
	this->CallUpdate = CallUpdate;
	std::cout << "Component Base Created" << std::endl;
}

void Component::Serialize()
{
}

void Component::Update()
{
	
}

bool& Component::get_CallUpdate()
{
	return _CallUpdate;
}

void Component::set_CallUpdate(bool value)
{
	_CallUpdate = value;
	if (_CallUpdate)
	{
		GameManager::AddUpdateCallback(updateCallback);
	}else
	{
		GameManager::RemoveUpdateCallback(updateCallback);
	}
}

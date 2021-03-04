#include "GameObjects/Components/Component.h"

#include <iostream>

#include "GameSystems/GameManager.h"
#include "Serialization/JsonArchive.h"

Component::Component(bool CallUpdate) :
	updateCallback([this]() { Update(); })
{
	static uint32_t ID = 0;

	this->_ComponentId = ID++;
	
	this->CallUpdate = CallUpdate;
	std::cout << "Component Base Created" << std::endl;
}

bool Component::IsOfType(const char* rawName)
{
	return typeid(this).name() == rawName;
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

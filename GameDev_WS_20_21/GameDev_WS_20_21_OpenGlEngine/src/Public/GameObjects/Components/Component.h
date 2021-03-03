#pragma once
#include <iostream>

#include "GameSystems/Callbacks.h"
#include "Tools/MacroCommon.h"

class GameObject;

/// <summary>
/// Base class holding common data for all derived components
/// </summary>
class Component
{
public:
	Component() = delete;
	Component(bool CallUpdate);
	virtual ~Component() { std::cout << "Component Base Destroyed" << std::endl; }

protected:
	virtual void Update();

public:
	CUSTOM_READ_WRITE_ATTRIB(bool, CallUpdate)
	GameObject* gameObject;

private:
	EngineCallback updateCallback;
};

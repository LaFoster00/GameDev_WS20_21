#pragma once
#include <iostream>
#include <nlohmann/json.hpp>


#include "GameSystems/Callbacks.h"
#include "Tools/MacroCommon.h"

class JsonOutputArchive;
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

	virtual bool IsOfType(const char* rawName);
	virtual void NotifyAttach() = 0;
	virtual void NotifyDetach() = 0;
	virtual nlohmann::ordered_json Serialize() = 0;

protected:
	virtual void Update() {}
	virtual void Deserialize(nlohmann::ordered_json& serializedComponent) { };

public:
	CUSTOM_READ_WRITE_ATTRIB(bool, CallUpdate)
	GameObject* gameObject;

	SIMPLE_READONLY_ATTRIB(uint32_t, ComponentId)
private:
	EngineCallback updateCallback;
};

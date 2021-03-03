#pragma once
#include "EventSystem.h"

class RenderSceneEvent : Event
{
public:
	EVENT_CLASS_TYPE(RenderScene)
	EVENT_CLASS_CATEGORY(EC_Engine)
};

class RenderGuiEvent : Event
{
public:
	EVENT_CLASS_TYPE(RenderGui)
	EVENT_CLASS_CATEGORY(EC_Engine)
};

class EngineUpdate : Event
{
public:
	EVENT_CLASS_TYPE(Update)
		EVENT_CLASS_CATEGORY(EC_Engine)
};
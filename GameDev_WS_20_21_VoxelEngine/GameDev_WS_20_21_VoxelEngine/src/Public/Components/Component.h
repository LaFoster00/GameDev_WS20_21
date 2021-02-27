#pragma once
#include <string>

#include "GameObject.h"

class Component
{
public:
	Component();
	virtual ~Component() {}

public:
	GameObject* gameObject;
};

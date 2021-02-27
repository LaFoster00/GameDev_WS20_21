#pragma once
#include <string>

#include "GameObject.h"

class Component
{
public:
	virtual ~Component() {}

	GameObject* gameObject;
};

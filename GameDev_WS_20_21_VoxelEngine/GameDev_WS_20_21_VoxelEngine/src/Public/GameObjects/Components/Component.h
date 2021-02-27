#pragma once
#include <iostream>

class GameObject;

/// <summary>
/// Base class holding common data for all derived components
/// </summary>
class Component
{
public:
	Component();
	virtual ~Component() { std::cout << "Component Base Destroyed" << std::endl; }

public:
	GameObject* gameObject;
};

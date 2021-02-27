#pragma once

#include "Component.h"
#include "Tools/MacroCommon.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


/// <summary>
/// Holds all the transform data as well as goodies such as forward vector
/// </summary>
class Transform : public Component
{
public:
	Transform();
	Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation);

public:
	glm::vec3 Location;
	glm::vec3 Scale;
	CUSTOMREADWRITEATTRIB(glm::quat, Rotation)
	glm::vec3 Forward;
};
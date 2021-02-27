#pragma once

#include "Component.h"
#include "Tools/MacroCommon.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform : Component
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
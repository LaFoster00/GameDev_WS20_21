#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Component.h"
#include "Tools/MacroCommon.h"


/// <summary>
/// Holds all the transform data as well as goodies such as forward vector
/// </summary>
class Transform : public Component
{
public:
	Transform();
	Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation);

	glm::mat4 GetModelMatrix() const;

	virtual nlohmann::ordered_json Serialize();

public:
	glm::vec3 Location;
	glm::vec3 Scale;
	CUSTOM_READ_WRITE_ATTRIB(glm::vec3, Rotation)
	glm::vec3 Forward;
};
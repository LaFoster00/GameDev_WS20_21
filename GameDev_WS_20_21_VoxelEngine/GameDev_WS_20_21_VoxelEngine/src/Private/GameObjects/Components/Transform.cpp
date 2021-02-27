#include "GameObjects/Components/Transform.h"

#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/quaternion.hpp"

Transform::Transform() : Location(0), Scale(1), _Rotation(glm::vec3(0)), Forward(glm::vec3(1, 0 ,0))
{
}

Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation)
{
	Location = pos;
	Scale = scale;
	Rotation = glm::quat(rotation);
}

glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 scale = glm::scale(Scale);
	glm::mat4 rotation = glm::toMat4(Rotation);
	glm::mat4 translation = glm::translate(glm::mat4(1), Location);

	return scale * rotation * translation;
}

glm::quat& Transform::get_Rotation()
{
	return _Rotation;
}

void Transform::set_Rotation(glm::quat value)
{
	_Rotation = glm::quat(value);
	Forward = value * glm::vec3(1, 0, 0);
}

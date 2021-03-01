#include "GameObjects/Components/Transform.h"

Transform::Transform() : Location(0), Scale(1), _Rotation(0), Forward(glm::vec3(1, 0 ,0))
{
}

Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation)
{
	Location = pos;
	Scale = scale;
	Rotation = rotation;
}

glm::mat4 Transform::GetModelMatrix() const
{
	const glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
	
	const glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(_Rotation)));
	const glm::mat4 translation = glm::translate(glm::mat4(1), Location);

	return translation * rotation * scale;
}

glm::vec3& Transform::get_Rotation()
{
	return _Rotation;
}

void Transform::set_Rotation(glm::vec3 value)
{
	_Rotation = value;
	Forward = glm::quat(glm::radians(_Rotation)) * glm::vec3(1, 0, 0);
}

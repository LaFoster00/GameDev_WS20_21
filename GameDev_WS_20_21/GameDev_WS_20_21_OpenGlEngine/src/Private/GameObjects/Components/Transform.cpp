#include "GameObjects/Components/Transform.h"

#include "Serialization/IArchive.h"

Transform::Transform() : Component(false) , Location(0), Scale(1), _Rotation(0), Forward(glm::vec3(1, 0 ,0))
{
}

Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation) : Component(false)
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

nlohmann::ordered_json Transform::Serialize()
{
	nlohmann::ordered_json transformSerialized = nlohmann::json::object();

	transformSerialized["Location"] = nlohmann::json::array({
		{"X", Location.x},
		{"Y", Location.y},
		{"Z", Location.z}
		});
	transformSerialized["Rotation"] = nlohmann::json::array({
		{"X", Rotation.x},
		{"Y", Rotation.y},
		{"Z", Rotation.z}
		});
	transformSerialized["Scale"] = nlohmann::json::array({
		{"X", Scale.x},
		{"Y", Scale.y},
		{"Z", Scale.z}
		});

	return transformSerialized;
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

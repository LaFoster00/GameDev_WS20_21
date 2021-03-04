#include "GameObjects/Components/Transform.h"

Transform::Transform() : Component(false) , Location(0), Scale(1), _Rotation(0), _Forward(glm::vec3(1, 0 ,0))
{
}

Transform::Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation) : Component(false)
{
	Location = pos;
	Scale = scale;
	Rotation = rotation;
}

Transform::Transform(nlohmann::ordered_json& serializedComponent) : Component(false), Location(0), Scale(1), _Rotation(0), _Forward(glm::vec3(1, 0, 0))
{
	Deserialize(serializedComponent);
}

void Transform::NotifyAttach()
{
	
}

void Transform::NotifyDetach()
{
	
}

glm::mat4 Transform::GetModelMatrix(bool invertTranslation) const
{
	const glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
	
	const glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(_Rotation)));
	const glm::mat4 translation = glm::translate(glm::mat4(1), invertTranslation? -Location : Location);

	return translation * rotation * scale;
}

nlohmann::ordered_json Transform::Serialize()
{
	nlohmann::ordered_json transformSerialized;
	transformSerialized["Type"] = typeid(Transform).name();
	transformSerialized["Location"] = nlohmann::json({
		{"X", Location.x},
		{"Y", Location.y},
		{"Z", Location.z}
		});
	transformSerialized["Rotation"] = nlohmann::json({
		{"X", Rotation.x},
		{"Y", Rotation.y},
		{"Z", Rotation.z}
		});
	transformSerialized["Scale"] = nlohmann::json({
		{"X", Scale.x},
		{"Y", Scale.y},
		{"Z", Scale.z}
		});

	return transformSerialized;
}

void Transform::Deserialize(nlohmann::ordered_json& serializedComponent)
{
	for (auto locationComp : serializedComponent["Location"].items())
	{
		if (locationComp.key() == "X")
			Location.x = locationComp.value();
		else if (locationComp.key() == "Y")
			Location.y = locationComp.value();
		else if (locationComp.key() == "Z")
			Location.z = locationComp.value();
	}

	for (auto rotationComp : serializedComponent["Rotation"].items())
	{
		if (rotationComp.key() == "X")
			Rotation.x = rotationComp.value().get<float>();
		else if (rotationComp.key() == "Y")
			Rotation.y = rotationComp.value().get<float>();
		else if (rotationComp.key() == "Z")
			Rotation.z = rotationComp.value().get<float>();
	}

	for (auto scaleComp : serializedComponent["Scale"].items())
	{
		if (scaleComp.key() == "X")
			Scale.x = scaleComp.value().get<float>();
		else if (scaleComp.key() == "Y")
			Scale.y = scaleComp.value().get<float>();
		else if (scaleComp.key() == "Z")
			Scale.z = scaleComp.value().get<float>();
	}
}

glm::vec3& Transform::get_Rotation()
{
	return _Rotation;
}

void Transform::set_Rotation(glm::vec3 value)
{
	_Rotation = value;
}

glm::vec3 Transform::get_Forward()
{
	return _Forward = glm::quat(glm::radians(_Rotation)) * glm::vec3(1, 0, 0);
}

glm::vec3 Transform::get_Right()
{
	return _Right = glm::quat(glm::radians(_Rotation)) * glm::vec3(0, 0, 1);
}

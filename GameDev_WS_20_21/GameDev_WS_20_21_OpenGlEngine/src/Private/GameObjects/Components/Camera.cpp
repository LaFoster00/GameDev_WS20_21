#include "GameObjects/Components/Camera.h"

#include "Rendering/Display.h"
#include "Rendering/Renderer.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Transform.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>


Camera::Camera(): Component(false)
{
	Renderer::MainCamera = this;
	cameraSettings = CameraRenderSettings();
}

Camera::Camera(CameraRenderSettings cameraSettings, bool isMainCamera) : Component(false)
{
	if (isMainCamera)
	Renderer::MainCamera = this;
	
	this->cameraSettings = cameraSettings;
}

Camera::Camera(nlohmann::ordered_json& serializedCamera): Component(false)
{
	Deserialize(serializedCamera);
}

Camera::~Camera()
{
	Renderer::MainCamera = Renderer::MainCamera == this ? nullptr : Renderer::MainCamera;
}

void Camera::NotifyAttach()
{
	m_transform = gameObject->GetComponentOfType<Transform>();
}

void Camera::NotifyDetach()
{
	
}

nlohmann::ordered_json Camera::Serialize()
{
	nlohmann::ordered_json cameraSerialized;
	cameraSerialized["MainCamera"] = Renderer::MainCamera == this;
	cameraSerialized["Type"] = typeid(Camera).name();
	cameraSerialized["Fov"] = cameraSettings.fov;
	cameraSerialized["NearPlane"] = cameraSettings.nearPlane;
	cameraSerialized["FarPlane"] = cameraSettings.farPlane;
	cameraSerialized["RenderMode"] = cameraSettings.renderMode;

	return cameraSerialized;
}

glm::mat4 Camera::get_ViewProjectMat()
{
	if (!m_transform) return _ViewProjectMat;

	const glm::vec2 resolution = glm::max(Display::GetWindowDimensions(), glm::vec2(1));
	const float aspectRatio = resolution.x / resolution.y;
	switch (cameraSettings.renderMode)
	{
		case RenderMode::PERSPECTIVE:
			//make sure fov is always in radians
			m_projectMat = glm::perspective( glm::radians(cameraSettings.fov), aspectRatio, cameraSettings.nearPlane, cameraSettings.farPlane);
			break;
		case RenderMode::ORTHOGRAPHIC:
			float sizeX = cameraSettings.fov;
			float sizeY = cameraSettings.fov;
			m_projectMat = glm::ortho(sizeX / -2.0f, sizeX / 2.0f, sizeY / -2.0f, sizeY / 2.0f, cameraSettings.nearPlane, cameraSettings.farPlane);
			break;
	}

	//const glm::mat4 view = glm::lookAt(m_transform->Location, m_transform->Location + m_transform->Forward, glm::vec3(0, 1, 0));

	
	const glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(m_transform->Rotation)));
	const glm::mat4 translation = glm::translate(glm::mat4(1), -m_transform->Location);
	
	glm::mat4 output = m_projectMat * rotation * translation;
	return output;
}

void Camera::Deserialize(nlohmann::ordered_json& serializedComponent)
{
	Renderer::MainCamera = serializedComponent["MainCamera"].get<bool>() ? this : Renderer::MainCamera;
	cameraSettings.fov = serializedComponent["Fov"].get<float>();
	int renderMode = serializedComponent["RenderMode"].get<int>();
	cameraSettings.renderMode = (RenderMode)renderMode;
	cameraSettings.farPlane = serializedComponent["FarPlane"].get<float>();
	cameraSettings.nearPlane = serializedComponent["NearPlane"].get<float>();
}

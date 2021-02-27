#include "Components/Camera.h"
#include "Components/GameObject.h"
#include "Components/Transform.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Rendering/Display.h"
#include "Rendering/Renderer.h"

Camera::Camera()
{
	cameraSettings = CameraRenderSettings();
}

Camera::Camera(CameraRenderSettings cameraSettings, bool isMainCamera)
{
	Renderer::mainCamera = this;

	this->cameraSettings = cameraSettings;
}

glm::mat4& Camera::get_ViewProjectMat()
{
	if (!m_transform)
	{
		if (gameObject)
		{
			m_transform = gameObject->GetComponentOfType<Transform>();
		}
		
		if (!m_transform) return _ViewProjectMat;
	}

	const glm::vec2 resolution = Display::GetWindowDimensions();
	switch (cameraSettings.renderMode)
	{
	case RenderMode::PERSPECTIVE:
		m_projectMat = glm::perspectiveFov( cameraSettings.fov, resolution.x, resolution.y, cameraSettings.nearPlane, cameraSettings.farPlane);
		break;
	case RenderMode::ORTHOGRAPHIC:
		const float aspectRatio = resolution.x / resolution.y;
		float sizeX = aspectRatio * cameraSettings.fov;
		float sizeY = cameraSettings.fov;
		m_projectMat = glm::ortho(sizeX / -2.0f, sizeX / 2.0f, sizeY / -2.0f, sizeY / 2.0f, cameraSettings.nearPlane, cameraSettings.farPlane);
		break;
	}

	glm::mat4 view = glm::translate(glm::mat4(1.0f), -m_transform->Location);
	view = glm::toMat4(m_transform->Rotation) * view;

	view = view * m_projectMat;
	
	return view;
}

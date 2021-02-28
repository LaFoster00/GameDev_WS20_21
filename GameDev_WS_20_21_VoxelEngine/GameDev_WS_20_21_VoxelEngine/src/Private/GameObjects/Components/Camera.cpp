#include "GameObjects/Components/Camera.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Transform.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Rendering/Display.h"
#include "Rendering/Renderer.h"

Camera::Camera()
{
	Renderer::mainCamera = this;
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

	
	glm::mat4 view = glm::lookAt(
		m_transform->Location, 
		glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0)  
	);
	glm::mat4 tranlation = glm::mat4(1.0f); //glm::translate(glm::mat4(1.0f), -m_transform->Location);
	
	glm::mat4 output = m_projectMat * view * tranlation ;
	return output;
}

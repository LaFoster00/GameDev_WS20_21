#pragma once

#include "Component.h"
#include "glm/glm.hpp"

#include "Tools/MacroCommon.h"

class Transform;

enum class RenderMode
{
	PERSPECTIVE = 0,
	ORTHOGRAPHIC = 1
};

struct CameraRenderSettings
{
	float fov;
	float nearPlane;
	float farPlane;
	RenderMode renderMode;

	CameraRenderSettings()
	{
		nearPlane = 0.1f;
		farPlane = 100.0f;
		fov = 80.0f;
		renderMode = RenderMode::PERSPECTIVE;
	}
};

class Camera : public Component
{
public:
	Camera();
	Camera(CameraRenderSettings cameraSettings, bool isMainCamera = true);

	CUSTOMREADONLYATTRIB(glm::mat4, ViewProjectMat)

	CameraRenderSettings cameraSettings;

private:
	Transform* m_transform;
	glm::mat4 m_projectMat;
};

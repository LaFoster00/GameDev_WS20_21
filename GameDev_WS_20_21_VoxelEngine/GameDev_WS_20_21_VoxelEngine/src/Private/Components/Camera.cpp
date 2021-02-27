#include "Components/Camera.h"

#include "Rendering/Renderer.h"

Camera::Camera()
{
	
}

Camera::Camera(bool isMainCamera)
{
	Renderer::mainCamera = this;
}

#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

/// <summary>
/// This class handles GLFW and OpenGL initiation as well as termination
/// Terminating GLFW in here ensures the OpenGL context will be valid until
/// all the buffers etc. are cleaned up.
/// </summary>

struct DisplaySettings
{
	uint32_t resX;
	uint32_t resY;
	std::string name;
	bool VSync;
	uint32_t glMajor;
	uint32_t glMinor;
	int glProfile;

	DisplaySettings()
	{
		resX = 640;
		resY = 480;
		name = "Voxel Engine";
		VSync = false;
		glMajor = 3;
		glMinor = 3;
		glProfile = GLFW_OPENGL_CORE_PROFILE;
	}
	
};

class Display
{
public:
	~Display();
	
	static GLFWwindow* InitiDisplay(const DisplaySettings settings);
	
	static GLFWwindow* GetWindow();

	static glm::vec2 GetWindowDimensions();
	
private:
	static GLFWwindow* m_window;
	static DisplaySettings m_settings;
};

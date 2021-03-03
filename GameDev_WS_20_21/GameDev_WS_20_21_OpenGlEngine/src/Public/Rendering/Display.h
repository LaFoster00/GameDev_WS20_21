#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

/// <summary>
/// This class handles GLFW and OpenGL initiation as well as termination
/// Terminating GLFW in here ensures the OpenGL context will be valid until
/// all the buffers etc. are cleaned up.
/// </summary>

class Display
{
public:
	~Display();
	
	static GLFWwindow* InitiDisplay();
	
	static GLFWwindow* GetWindow();

	static glm::vec2 GetWindowDimensions();
	
private:
	static GLFWwindow* m_window;
};

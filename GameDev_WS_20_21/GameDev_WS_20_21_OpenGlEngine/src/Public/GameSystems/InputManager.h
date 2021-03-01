#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "Rendering/Display.h"


class InputManager
{
public:
	static void InitInput()
	{
		glfwSetCursorPosCallback(Display::GetWindow(), cursor_position_callback);
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(Display::GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	}
	
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseMovement = glm::vec2(xpos, ypos) - m_lastMousePosition;
		m_lastMousePosition = glm::vec2(xpos, ypos);
	}

public:
	static glm::vec2 mouseMovement;

private:
	static glm::vec2 m_lastMousePosition;
};

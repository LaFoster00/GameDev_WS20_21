#pragma once

#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
	~Display()
	{
		glfwTerminate();
	}
	
	static GLFWwindow* InitiDisplay(
		const uint32_t resX = 640,
		const uint32_t resY = 480, 
		const char* name = "Voxel Engine",
		const uint32_t glMajor = 4,
		const uint32_t glMinor = 1,
		const int glProfile = GLFW_OPENGL_CORE_PROFILE);
	static GLFWwindow* GetWindow();
	
private:
	static GLFWwindow* m_window;
	static Display s_instance;
};
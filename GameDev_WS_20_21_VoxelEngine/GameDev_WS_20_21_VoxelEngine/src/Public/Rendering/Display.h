#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui_impl_glfw.h"
/// <summary>
/// This class handles GLFW and OpenGL initiation as well as termination
/// Terminating GLFW in here ensures the OpenGL context will be valid until
/// all the buffers etc. are cleaned up.
/// </summary>

struct DisplaySettings
{
	const uint32_t resX = 640;
	const uint32_t resY = 480;
	const char* name = "Voxel Engine";
	const bool VSync = false;
	const uint32_t glMajor = 3;
	const uint32_t glMinor = 3;
	const int glProfile = GLFW_OPENGL_CORE_PROFILE;

	DisplaySettings(){}
};

class Display
{
public:
	~Display()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}
	
	static GLFWwindow* InitiDisplay(const DisplaySettings& settings);
	
	static GLFWwindow* GetWindow();
	
private:
	static GLFWwindow* m_window;
};

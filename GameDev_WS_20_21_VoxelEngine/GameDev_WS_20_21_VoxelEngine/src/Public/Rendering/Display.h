#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "imgui/imgui_impl_glfw.h"
/// <summary>
/// This class handles GLFW and OpenGL initiation as well as termination
/// Terminating GLFW in here ensures the OpenGL context will be valid until
/// all the buffers etc. are cleaned up.
/// </summary>

class Display
{
public:
	~Display()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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
};
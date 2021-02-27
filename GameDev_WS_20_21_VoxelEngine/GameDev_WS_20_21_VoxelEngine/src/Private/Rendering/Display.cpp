#include "Rendering/Display.h"

#include <iostream>

#include "imgui/imgui_impl_opengl3.h"

GLFWwindow* Display::m_window;

GLFWwindow* Display::InitiDisplay(const DisplaySettings& settings)
{
	static bool Initialized = false;

	if (Initialized) return m_window;

	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.glMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.glMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, settings.glProfile);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(settings.resX, settings.resY, settings.name, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return nullptr;
	}
	
	glfwMakeContextCurrent(m_window);

	/* Init glew */
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew Init Error" << std::endl;
	}
	
	glDisable(GL_STENCIL_TEST);
	glfwSwapInterval(settings.VSync);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	
	return m_window;
}

GLFWwindow* Display::GetWindow()
{
	return m_window;
}

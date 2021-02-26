#include "Rendering/Display.h"

GLFWwindow* Display::m_window;

GLFWwindow* Display::InitiDisplay(
	const uint32_t resX,
	const uint32_t resY, 
	const char* name, 
	const uint32_t glMajor, 
	const uint32_t glMinor, 
	const int glProfile)
{
	static bool Initialized = false;

	if (Initialized) return m_window;

	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, glProfile);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(resX, resY, name, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return nullptr;
	}

	return m_window;
}

GLFWwindow* Display::GetWindow()
{
	return m_window;
}

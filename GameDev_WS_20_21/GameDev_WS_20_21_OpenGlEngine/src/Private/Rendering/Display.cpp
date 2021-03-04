#include "Rendering/Display.h"

#include <iostream>
#include <GL/glew.h>

#include "DebugTools.h"
#include "imgui/imgui.h"
#include "Serialization/EngineArchive.h"

#ifdef WITH_IMGUI
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#endif

GLFWwindow* Display::m_window;

Display::~Display()
{
#ifdef WITH_IMGUI
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif
	glfwTerminate();
}

GLFWwindow* Display::InitiDisplay()
{
	static bool Initialized = false;
	

	if (Initialized) return m_window;
	
	/* Initialize the library */
	if (!glfwInit())
		return nullptr;

	/* Set glfw settings */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, EngineArchive::Get()->glMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, EngineArchive::Get()->glMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(EngineArchive::Get()->WindowSizeX, EngineArchive::Get()->WindowSizeY, EngineArchive::Get()->WindowName.c_str(), NULL, NULL);
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

	/* Set OpenGl features. */
#ifdef DEBUG_ENGINE
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
#endif

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);

	GLASSERTCALL(glEnable(GL_BLEND));
	GLASSERTCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	glDisable(GL_STENCIL_TEST);
	glfwSwapInterval(EngineArchive::Get()->VSync);

#ifdef WITH_IMGUI
	/* Set up ImGui */
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	char buffer[100];
	sprintf_s(buffer, "#version %d%d0", EngineArchive::Get()->glMajor, EngineArchive::Get()->glMinor);
	std::cout << "ImGui OpenGl Version: " << buffer << std::endl;
	
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(buffer);

	std::cout << "Imgui Activated!" << std::endl;
#endif	
	return m_window;
}

GLFWwindow* Display::GetWindow()
{
	return m_window;
}

glm::vec2 Display::GetWindowDimensions()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	return glm::vec2(width, height);
}

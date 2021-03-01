#include "Engine.h"

#include <iostream>

#include "GameSystems/EngineTime.h"
#include "GameSystems/GameManager.h"
#include "Rendering/Display.h"
#include "Rendering/Renderer.h"


void Engine::Init()
{
	GameManager::Init();
	/* Init GLFW and Window */
	DisplaySettings settings;
	settings.resX = 640 * 2;
	settings.resY = 480 * 2;
	Display::InitiDisplay(settings);

	std::cout << glGetString(GL_VERSION) << std::endl;
}

void Engine::ShutDown()
{
	GameManager::ShutDown(); // Should be removed last as this will destroy all game objects that still exist
}

void Engine::Update()
{
	/* Engine Loop */
	{
		Time::UpdateGameTime();
	}

	/* Render Loop */
	{
		/* Clear screen */
		Renderer::Clear();

#ifdef WITH_IMGUI
		/* IMGUI stuffelonious */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		std::cout << "Imgui Activated!" << std::endl;
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

		/* Swap front and back buffers */
		glfwSwapBuffers(Display::GetWindow());
	}

	/* Poll for and process events */
	glfwPollEvents();
}

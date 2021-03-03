#include "Engine.h"

#include <iostream>
#include <fstream>

#include "GameSystems/EngineTime.h"
#include "GameSystems/GameManager.h"

#ifdef WITH_IMGUI
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#endif

#include "Rendering/Display.h"
#include "Rendering/Renderer.h"
#include "Serialization/EngineArchive.h"


void Engine::Init()
{
	EngineArchive::LoadEngineConfig("EngineConfig.config");
	
	/* Init GLFW and Window */
	Display::InitiDisplay();

	std::cout << "OpenGl: " << glGetString(GL_VERSION) << std::endl;

	GameManager::Init();
}

void Engine::ShutDown()
{
	GameManager::ShutDown(); // Should be removed last as this will destroy all game objects that still exist
	EngineArchive::SaveEngineConfig();
}

void Engine::Update()
{
	/* Engine Loop */
	{
		Time::UpdateGameTime();
		GameManager::Update();
	}

	/* Render Loop */
	{
		/* Clear screen */
		Renderer::Clear();

		Renderer::RenderScene();
		
#ifdef WITH_IMGUI
		/* IMGUI stuffelonious */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Renderer::RenderGui();
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

		/* Swap front and back buffers */
		glfwSwapBuffers(Display::GetWindow());
	}

	/* Poll for and process events */
	glfwPollEvents();
}

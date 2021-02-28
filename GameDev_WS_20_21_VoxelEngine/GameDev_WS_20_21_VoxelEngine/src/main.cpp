#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Data/Mesh.h"
#include "Data/Texture.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "GameSystems/EngineTime.h"
#include "GameSystems/GameManager.h"
#include "GameSystems/InputManager.h"
#include "Rendering/Display.h"
#include "Rendering/Shader.h"
#include "Rendering/Renderer.h"
#include "Tools/ObjImporter.h"

#include "glm/glm.hpp"

#ifdef WITH_EDITOR
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Editor/EditorManager.h"
#endif

int main(void)
{
	/* Init GLFW and Window */
	DisplaySettings settings;
	settings.resX = 640 * 2;
	settings.resY = 480 * 2;
	Display::InitiDisplay(settings);

	GameManager* gameManager = new GameManager();
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Create Camera and set it up
	GameObject* CameraObject = GameManager::AddGameObject("Camera", glm::vec3(0, 1, -2), glm::vec3(0));
	Camera* camera = new Camera();
	camera->cameraSettings.renderMode = RenderMode::PERSPECTIVE;
	camera->cameraSettings.fov = 90.0f;
	camera->cameraSettings.nearPlane = 0.01f;
	camera->cameraSettings.farPlane = 10.0f;
	CameraObject->AddComponent(camera);

	Texture texture("res/textures/Test.jpg");
	texture.Bind(0);

	Shader shader("res/shaders/Basic.shader");
	
	//create cube object from imported cube mesh
	// Setup Material for cube
	Material material = Material(&shader);
	uint32_t textureSlot = 0;
	material.SetUniform("_Texture", textureSlot);

	//Setup Mesh for cube
	Mesh* mesh = LoadObj("res/models/Monkey.obj");
	MeshRenderer* cubeRenderer = new MeshRenderer(mesh, &material);

	//Setup GameObject for cube
	GameObject* importedObject = GameManager::AddGameObject("Cube", glm::vec3(0, 0, 0), glm::vec3(0));
	//Add previously setup Mesh Renderer component
	importedObject->AddComponent(cubeRenderer);

	glm::vec3 translation2;
	
	std::cout << "Main Engine Loop:\n" << std::endl;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Display::GetWindow()))
	{
		/* Engine Loop */
		{
			Time::UpdateGameTime();
		}
			
		/* Render Loop */
		{
			/* Clear screen */
			Renderer::Clear();

#ifdef WITH_EDITOR
			/* IMGUI stuffelonious */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			EditorManager::RenderEditor();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

			/* Swap front and back buffers */
			glfwSwapBuffers(Display::GetWindow());
		}

		/* Poll for and process events */  
		glfwPollEvents();
	}

	delete gameManager; // Should be removed last as this will destroy all game objects that still exist
	
	return 0;
}

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "EngineTime.h"
#include "DebugTools.h"
#include "Data/Mesh.h"
#include "Data/Texture.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "Rendering/Display.h"
#include "Rendering/Shader.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Renderer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Tools/ObjImporter.h"

int main(void)
{
	/* Init GLFW and Window */
	DisplaySettings settings;
	Display::InitiDisplay(settings);
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	GLASSERTCALL(glEnable(GL_BLEND));
	GLASSERTCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Create Camera and set it up
	GameObject CameraObject("Camera", glm::vec3(0), glm::vec3(0));
	Camera* camera = new Camera();
	camera->cameraSettings.renderMode = RenderMode::PERSPECTIVE;
	camera->cameraSettings.fov = 60.0f;
	camera->cameraSettings.nearPlane = 0.01f;
	camera->cameraSettings.farPlane = 10.0f;
	CameraObject.AddComponent(camera);

	Texture texture("res/textures/Test.jpg");
	texture.Bind(0);

	Shader shader("res/shaders/Basic.shader");
	
	//Create Debug Plane PPP UV NNN
	float positions[] = {
		-0.5f,	-0.5f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		 0.5f,	-0.5f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		 0.5f,	 0.5f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f,
		-0.5f,	 0.5f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,
	};

	uint32_t indices[] = {
		0 , 1 , 2 ,
		2 , 3 , 0
	};

	Material debugMaterial = Material(&shader);
	uint32_t deubgTextureSlot = 0;
	debugMaterial.SetUniform("_Texture", deubgTextureSlot);
	
	Mesh* debugMesh = new Mesh(positions, 4 * sizeof(float) * 8, indices, 6);
	MeshRenderer debugMeshRenderer(debugMesh, &debugMaterial);

	GameObject debugObject("Debug", glm::vec3(0), glm::vec3(0));
	debugObject.AddComponent(&debugMeshRenderer);
	
	//create cube object from imported cube mesh
	// Setup Material for cube
	Material material = Material(&shader);
	uint32_t textureSlot = 0;
	material.SetUniform("_Texture", textureSlot);

	//Setup Mesh for cube
	Mesh* mesh = LoadObj("res/models/Cube.obj");
	MeshRenderer cubeRenderer(mesh, &material);

	//Setup GameObject for cube
	GameObject cube("Cube", glm::vec3(0, 0, 3), glm::vec3(0));
	//Add previously setup Mesh Renderer component
	cube.AddComponent(&cubeRenderer);

	glm::vec3 translation2;
	
	std::cout << "Main Engine Loop:\n" << std::endl;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Display::GetWindow()))
	{
		/* Clear screen */
		Renderer::Clear();
		
		/* Update Game Time System */
		{
			Time::UpdateGameTime();
			/* Update DeltaTime And FPS print */
			//std::cout << "\r" << "DeltaTime: " << Time::DeltaTime << std::flush;
		}

		debugMeshRenderer.Render();
		cubeRenderer.Render();
		
		/* IMGUI stuffelonious */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::SliderFloat3("Translation 1", &camera->gameObject->GetComponentOfType<Transform>()->Location.x, -2.0f, 2.0f);
			ImGui::SliderFloat3("Translation 2", &translation2.x, -2.0f, 2.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(Display::GetWindow());

		/* Poll for and process events */  
		glfwPollEvents();
	}
	
	return 0;
}

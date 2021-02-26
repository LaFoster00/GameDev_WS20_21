#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "EngineTime.h"
#include "DebugTools.h"
#include "Data/Texture.h"
#include "Rendering/Display.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
	/* Init GLFW and Window */
	Display::InitiDisplay();
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	GLASSERTCALL(glEnable(GL_BLEND));
	GLASSERTCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
	float positions[] = {
		-0.5f,	-0.5f,	0.0f,	0.0f,
		 0.5f,	-0.5f,	1.0f,	0.0f,
		 0.5f,	 0.5f,	1.0f,	1.0f,
		-0.5f,	 0.5f,	0.0f,	1.0f,
	};

	uint32_t indices[] = {
		0 , 1 , 2 ,
		2 , 3 , 0 
	};

	VertexArray vertexArray;

	VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout vertexLufferLayout;
	vertexLufferLayout.Push<float>(2);
	vertexLufferLayout.Push<float>(2);
	
	vertexArray.AddBuffer(vertexBuffer, vertexLufferLayout);
	
	IndexBuffer indexBuffer(indices, 6);

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.25f, 0.0f));
	
	glm::mat4 mvp = proj * view * model;
	
	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	Texture texture("res/textures/Test.jpg");
	texture.Bind(0);
	
	vertexArray.Unbind();
	shader.Unbind();
	vertexBuffer.Unbind();
	indexBuffer.Unbind();

	Renderer renderer;
	
	float r = 0.0f;
	double increment = 0;

	bool showDemoWindow = true;
	bool showAnotherWindow = false;
	ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
	
	std::cout << "Main Engine Loop:\n" << std::endl;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Display::GetWindow()))
	{
		/* Clear screen */
		renderer.Clear();
		
		/* Update Game Time System */
		{
			Time::UpdateGameTime();
			/* Update DeltaTime And FPS print */
			//std::cout << "\r" << "DeltaTime: " << Time::DeltaTime << " FPS: " << (1 / Time::DeltaTime) << std::flush;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		shader.Bind();
		texture.Bind(0);
		/* Modulate color before computing the vertex buffer */
		shader.SetUniform1i("_Texture", 0);
		shader.SetUniformMat4("_MVP", mvp);

		renderer.Draw(vertexArray, indexBuffer, shader);
		
		if (r >= 1.0f)
			increment = -2;
		else if (r <= 0.0f)
			increment = 2;

		r += Time::DeltaTime * increment;

		{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Hello World!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clearColor);

			ImGui::Checkbox("Demo Window", &showDemoWindow);
			ImGui::Checkbox("Another Window", &showAnotherWindow);

			if (ImGui::Button("Button"))
			{
				counter++;
			}
			ImGui::SameLine();
			ImGui::Text("Counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		// 3. Show another simple window.
		if (showAnotherWindow)
		{
			ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				showAnotherWindow = false;
			ImGui::End();
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

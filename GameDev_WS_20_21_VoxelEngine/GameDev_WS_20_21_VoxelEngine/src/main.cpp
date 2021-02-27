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
	DisplaySettings settings;
	Display::InitiDisplay(settings);
	
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
	
	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	Texture texture("res/textures/Test.jpg");
	texture.Bind(0);
	
	vertexArray.Unbind();
	shader.Unbind();
	vertexBuffer.Unbind();
	indexBuffer.Unbind();

	Renderer renderer;

	glm::vec3 translation1(0);
	glm::vec3 translation2(0);
	
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
			//std::cout << "\r" << "DeltaTime: " << Time::DeltaTime << std::flush;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		glm::mat4 view(1);
		glm::mat4 model = glm::translate(glm::mat4(1.0f),translation1);

		glm::mat4 mvp = proj * view * model;

		shader.Bind();
		texture.Bind(0);
		
		/* Modulate color before computing the vertex buffer */
		shader.SetUniformSampler("_Texture", 0);
		shader.SetUniformMat4("_MVP", mvp);

		renderer.Draw(vertexArray, indexBuffer, shader);

		model = glm::translate(glm::mat4(1.0f), translation2);
		mvp = proj * view * model;
		
		shader.SetUniformMat4("_MVP", mvp);
		renderer.Draw(vertexArray, indexBuffer, shader);
		
		{
			ImGui::SliderFloat3("Translation 1", &translation1.x, -2.0f, 2.0f);
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

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

int main(void)
{
	/* Init GLFW and Window */
	Display::InitiDisplay();
	
	/* Make the window's context current and init glew */
	glfwMakeContextCurrent(Display::GetWindow());
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew Init Error" << std::endl;
	}
	
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
	std::cout << "Main Engine Loop:\n" << std::endl;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(Display::GetWindow()))
	{
		/* Update Game Time System */
		{
			Time::UpdateGameTime();
			/* Update DeltaTime And FPS print */
			//std::cout << "\r" << "DeltaTime: " << Time::DeltaTime << " FPS: " << (1 / Time::DeltaTime) << std::flush;
		}
		
		/* Render here */
		renderer.Clear();

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

		/* Swap front and back buffers */
		glfwSwapBuffers(Display::GetWindow());

		/* Poll for and process events */  
		glfwPollEvents();
	}
	
	return 0;
}

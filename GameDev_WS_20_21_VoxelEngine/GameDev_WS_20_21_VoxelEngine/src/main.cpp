#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "EngineTime.h"
#include "DebugTools.h"
#include "Rendering/Display.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"

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

	float positions[8] = {
		-0.5f,	-0.5f,
		 0.5f,	-0.5f,
		 0.5f,	 0.5f,
		-0.5f,	 0.5f
	};

	uint32_t indices[6] = {
		0 , 1 , 2 ,
		2 , 3 , 0 
	};

	VertexArray vertexArray;

	VertexBuffer vertexBuffer(positions, 8* sizeof(float));

	VertexBufferLayout vertexLufferLayout;
	vertexLufferLayout.Push<float>(2);
	
	vertexArray.AddBuffer(vertexBuffer, vertexLufferLayout);
	
	IndexBuffer indexBuffer(indices, 6);

	Shader shader("res/shaders/Basic.shader");
	shader.Bind();

	vertexArray.Unbind();
	shader.Unbind();
	vertexBuffer.Unbind();
	indexBuffer.Unbind();

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
			std::cout << "\r" << "DeltaTime: " << Time::DeltaTime << " FPS: " << (1 / Time::DeltaTime) << std::flush;
		}
		
		/* Render here */
		GLASSERTCALL(glClear(GL_COLOR_BUFFER_BIT));

		shader.Bind();
		/* Modulate color before computing the vertex buffer */
		shader.SetUniform4f("vertexColor", r*0.5f, 0.3f, 0.8f, 1.0f);

		vertexArray.Bind();
		vertexBuffer.Bind();
		indexBuffer.Bind();

		GLASSERTCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r >= 1.0f)
			increment = -2;
		else if (r <= 0.0f)
			increment = 2;

		r += Time::DeltaTime * increment;

		/* Swap front and back buffers */
		GLASSERTCALL(glfwSwapBuffers(Display::GetWindow()));

		/* Poll for and process events */  
		GLASSERTCALL(glfwPollEvents());
	}
	
	return 0;
}

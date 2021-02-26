#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderTools.h"
#include "EngineTime.h"
#include "DebugTools.h"
#include "Rendering/Display.h"
#include "Rendering/IndexBuffer.h"
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

	/* vertex buffer */
	VertexBuffer vertexBuffer(positions, 8* sizeof(float));

	VertexBufferLayout vertexLufferLayout;
	vertexLufferLayout.Push<float>(2);
	
	vertexArray.AddBuffer(vertexBuffer, vertexLufferLayout);
	
	/* Index Buffer */
	IndexBuffer indexBuffer(indices, 6);
	
	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	GLASSERTCALL(glUseProgram(shader));

	GLASSERTCALL(const int vertexColorLocation = glGetUniformLocation(shader, "vertexColor"));
	ASSERT(vertexColorLocation != -1);

	vertexArray.Unbind();
	GLASSERTCALL(glUseProgram(0));
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

		GLASSERTCALL(glUseProgram(shader));
		/* Modulate color before computing the vertex buffer */
		GLASSERTCALL(glUniform4f(vertexColorLocation, r*0.5f, 0.3f, 0.8f, 1.0f));

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

	GLASSERTCALL(glDeleteProgram(shader));

	
	return 0;
}

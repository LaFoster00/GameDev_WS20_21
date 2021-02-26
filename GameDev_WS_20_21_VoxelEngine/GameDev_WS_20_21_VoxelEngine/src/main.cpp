#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "ShaderTools.h"
#include "EngineTime.h"
#include "DebugTools.h"
#include "Rendering/Display.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexBuffer.h"

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

	uint32_t vertexArray;
	GLASSERTCCALL(glGenVertexArrays(1, &vertexArray));
	GLASSERTCCALL(glBindVertexArray(vertexArray));

	/* vertex buffer */
	VertexBuffer vertexBuffer(positions, 8* sizeof(float));

	GLASSERTCCALL(glEnableVertexAttribArray(0));
	GLASSERTCCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr)); /* define data layout for vertex positions */

	/* Index Buffer */
	IndexBuffer indexBuffer(indices, 6);
	
	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	GLASSERTCCALL(glUseProgram(shader));

	GLASSERTCCALL(const int vertexColorLocation = glGetUniformLocation(shader, "vertexColor"));
	ASSERT(vertexColorLocation != -1);

	GLASSERTCCALL(glBindVertexArray(0));
	GLASSERTCCALL(glUseProgram(0));
	GLASSERTCCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLASSERTCCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

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
		GLASSERTCCALL(glClear(GL_COLOR_BUFFER_BIT));

		GLASSERTCCALL(glUseProgram(shader));
		/* Modulate color before computing the vertex buffer */
		GLASSERTCCALL(glUniform4f(vertexColorLocation, r*0.5f, 0.3f, 0.8f, 1.0f));

		GLASSERTCCALL(glBindVertexArray(vertexArray));
		vertexBuffer.Bind();

		GLASSERTCCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r >= 1.0f)
			increment = -2;
		else if (r <= 0.0f)
			increment = 2;

		r += Time::DeltaTime * increment;

		/* Swap front and back buffers */
		GLASSERTCCALL(glfwSwapBuffers(Display::GetWindow()));

		/* Poll for and process events */  
		GLASSERTCCALL(glfwPollEvents());
	}

	GLASSERTCCALL(glDeleteProgram(shader));

	
	return 0;
}
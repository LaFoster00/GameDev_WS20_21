#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ShaderTools.h"
#include "DebugTools.h"
#include "EngineTime.h"

GLFWwindow* window;
float deltaTime;

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current and init glew */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew Init Error" << std::endl;
	}
	
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[4][2] = {
		{   -0.5f,  -0.5f   },
		{    0.5f,  -0.5f  },
		{    0.5f,	0.5f  },
		{   -0.5f,	0.5f  }
	};

	uint32_t indices[2][3] = {
		{ 0 , 1 , 2 },
		{ 2 , 3 , 0 }
	};

	uint32_t vertexArray;
	GLASSERTCCALL(glGenVertexArrays(1, &vertexArray));
	GLASSERTCCALL(glBindVertexArray(vertexArray));

	/* vertex buffer */
	uint32_t buffer;
	GLASSERTCCALL(glGenBuffers(1, &buffer));
	GLASSERTCCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLASSERTCCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW)); /* set the buffer data */

	GLASSERTCCALL(glEnableVertexAttribArray(0));
	GLASSERTCCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr)); /* define data layout for vertex positions */

	uint32_t indexBuffer;
	GLASSERTCCALL(glGenBuffers(1, &indexBuffer));
	GLASSERTCCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
	GLASSERTCCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
	
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
	while (!glfwWindowShouldClose(window))
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
		GLASSERTCCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));

		GLASSERTCCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r >= 1.0f)
			increment = -2;
		else if (r <= 0.0f)
			increment = 2;

		r += Time::DeltaTime * increment;

		/* Swap front and back buffers */
		GLASSERTCCALL(glfwSwapBuffers(window));

		/* Poll for and process events */  
		GLASSERTCCALL(glfwPollEvents());
	}

	GLASSERTCCALL(glDeleteProgram(shader));

	glfwTerminate();
	return 0;
}
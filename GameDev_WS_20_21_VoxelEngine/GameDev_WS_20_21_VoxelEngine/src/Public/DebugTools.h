#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define ASSERT(x) if (!(x)) __debugbreak()

#ifdef DEBUG_ENGINE

#define GLASSERTCCALL(x) \
	GLClearCall(); \
	x; \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__)) \

#else

#define GLASSERTCCALL(x) x;

#endif

static void GLClearCall()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") in Function: " << function << std::endl;
		std::cout << file << " : " << line << std::endl;
		return false;
	}
	return true;
}

void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << severity << " : [OpenGL Error](" << type << ") " << message << std::endl;
}
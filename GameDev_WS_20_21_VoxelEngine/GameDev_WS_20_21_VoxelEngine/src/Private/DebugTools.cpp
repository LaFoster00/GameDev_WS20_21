#include "DebugTools.h"

#include <iostream>

void GLClearCall()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") in Function: " << function << std::endl;
		std::cout << file << " : " << line << std::endl;
		return false;
	}
	return true;
}
#pragma once

#include <iostream>
#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()

#ifdef DEBUG_ENGINE

#define GLASSERTCALL(x) \
	GLClearCall(); \
	x; \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__)) \

#else

#define GLASSERTCALL(x) x;

#endif

void GLClearCall();

bool GLLogCall(const char* function, const char* file, int line);


void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar * message,
    const void* userParam);
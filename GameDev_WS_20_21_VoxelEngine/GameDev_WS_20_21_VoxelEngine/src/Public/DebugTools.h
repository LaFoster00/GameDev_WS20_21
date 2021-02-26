#pragma once

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak()

#ifdef DEBUG_ENGINE

#define GLASSERTCALL(x) \
	GLClearCall(); \
	x; \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__)) \

#else

#define GLASSERTCCALL(x) x;

#endif

void GLClearCall();

bool GLLogCall(const char* function, const char* file, int line);
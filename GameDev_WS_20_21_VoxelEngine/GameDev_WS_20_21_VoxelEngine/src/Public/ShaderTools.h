#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

ShaderProgramSource ParseShader(const std::string& filepath, const bool printParsedCode = true);

uint32_t CompileShader(uint32_t type, const std::string& source);

uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
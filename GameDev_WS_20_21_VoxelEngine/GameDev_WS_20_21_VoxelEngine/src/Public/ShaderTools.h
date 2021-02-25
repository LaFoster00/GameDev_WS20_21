#pragma once

#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

ShaderProgramSource ParseShader(const std::string& filepath);

uint32_t CompileShader(uint32_t type, const std::string& source);

uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
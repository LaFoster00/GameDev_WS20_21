#pragma once
#include <string>
#include <unordered_map>

#include "Rendering/Shader.h"

class ShaderManager
{
public:
	static Shader* GetShader(const std::string& filepath);
	static void ShutDown();

private:
	static std::unordered_map<std::string, Shader*> m_shader;
};

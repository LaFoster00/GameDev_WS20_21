#include "GameSystems/ShaderManager.h"

std::unordered_map<std::string, Shader*> ShaderManager::m_shader;

Shader* ShaderManager::GetShader(const std::string& filepath)
{
	if (m_shader.find(filepath) == m_shader.end())
	{
		Shader* shader = new Shader(filepath);
		m_shader[filepath] = shader;
	}

	return m_shader[filepath];
}

void ShaderManager::ShutDown()
{
	for (auto shader : m_shader)
	{
		delete shader.second;
	}
}

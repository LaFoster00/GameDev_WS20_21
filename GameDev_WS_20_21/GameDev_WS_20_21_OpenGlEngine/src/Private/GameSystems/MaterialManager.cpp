#include "GameSystems/MaterialManager.h"

#include "GameSystems/ShaderManager.h"
#include "Rendering/Material.h"

std::unordered_map<std::string, Material*> MaterialManager::m_materials;

Material* MaterialManager::GetMaterial(const std::string& shaderFilepath)
{
	if (m_materials.find(shaderFilepath) == m_materials.end())
	{
		Shader* shader = ShaderManager::GetShader(shaderFilepath);
		Material* material = new Material(shader);
		m_materials[shaderFilepath] = material;
	}

	return m_materials[shaderFilepath];
}

void MaterialManager::ShutDown()
{
	for (auto material : m_materials)
	{
		delete material.second;
	}
}

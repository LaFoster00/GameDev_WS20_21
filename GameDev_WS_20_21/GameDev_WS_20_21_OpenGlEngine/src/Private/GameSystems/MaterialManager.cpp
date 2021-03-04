#include "GameSystems/MaterialManager.h"

#include "GameSystems/ShaderManager.h"
#include "Rendering/Material.h"

std::unordered_map<std::string, Material*> MaterialManager::m_materials;
std::vector<Material*> MaterialManager::m_materialInstances;

Material* MaterialManager::GetDefaultMaterial(bool instance)
{
	return GetMaterial("Assets/shader/Basic.shader");
}

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

Material* MaterialManager::GetMaterialInstance(const std::string& shaderFilepath)
{

	Material* material = GetMaterial(shaderFilepath);

	if (material)
	{
		Material* materialInstance = new Material(*material);
		m_materialInstances.push_back(materialInstance);
		return materialInstance;
	}

	return nullptr;
}

void MaterialManager::ShutDown()
{
	for (auto material : m_materials)
	{
		delete material.second;
	}

	for (auto materiaInstance : m_materialInstances)
	{
		delete materiaInstance;
	}
}

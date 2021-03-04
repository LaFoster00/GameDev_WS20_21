#pragma once
#include <string>
#include <unordered_map>

class Material;

class MaterialManager
{
public:
	static Material* GetDefaultMaterial(bool instance = false);
	static Material* GetMaterial(const std::string& shaderFilepath);
	static Material* GetMaterialInstance(const std::string& shaderFilepath);
	
	static void ShutDown();
private:
	static std::unordered_map<std::string, Material*> m_materials;
	static std::vector<Material*> m_materialInstances;
};

#include "GameSystems/MeshManager.h"

#include <fstream>


#include "Tools/ObjImporter.h"

std::unordered_map<std::string, Mesh*> MeshManager::m_meshes;
std::unordered_map<std::string, Mesh*> MeshManager::m_meshesByName;

void MeshManager::ShutDown()
{
	for (auto mesh : m_meshes)
	{
		delete mesh.second;
	}
}

Mesh* MeshManager::LoadMesh(const std::string& filepath)
{
	if (m_meshes.find(filepath) == m_meshes.end())
	{
		std::ifstream testValid(filepath);
		if (!testValid.is_open()) return nullptr;
		
		m_meshes[filepath] = Tools::LoadObj(filepath);
		
		std::string fileWithoutEnding =  filepath.substr(0, filepath.find_last_of('.'));
		size_t lastSlash = filepath.find_last_of('/');
		std::string meshName = filepath.substr(lastSlash);
		
		m_meshesByName[meshName] = m_meshes[filepath];
	}

	if (m_meshes.find(filepath) != m_meshes.end())
	{
		return m_meshes[filepath];
	}

	return nullptr;
}

Mesh* MeshManager::GetMeshByName(const std::string& meshName)
{
	if (m_meshesByName.find(meshName) != m_meshesByName.end())
	{
		return m_meshesByName[meshName];
	}
	
	return nullptr;
}
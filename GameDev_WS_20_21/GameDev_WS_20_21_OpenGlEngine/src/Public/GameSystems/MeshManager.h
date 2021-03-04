#pragma once
#include <unordered_map>

#include "Data/Mesh.h"

class MeshManager
{
public:
	static void ShutDown();
	static Mesh* LoadMesh(const std::string& filepath);
	static Mesh* GetMeshByName(const std::string& meshName);

private:
	static std::unordered_map<std::string, Mesh*> m_meshes;
	static std::unordered_map<std::string, Mesh*> m_meshesByName;
};

#pragma once
#include "Component.h"
#include "GameSystems/Callbacks.h"

class Material;
class VertexArray;
class Mesh;
class Transform;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh* mesh, Material* material);
	MeshRenderer(nlohmann::ordered_json& serializedMeshRenderer);
	~MeshRenderer();

	void NotifyAttach() override;
	void NotifyDetach() override;
	
	void SetMesh(Mesh* mesh);
	void Render();

	nlohmann::ordered_json Serialize() override;

protected:
	void Deserialize(nlohmann::ordered_json& serializedComponent) override;
public:
	Material* material;
	Mesh* mesh;
private:
	Transform* m_transform;

	EngineCallback m_renderSceneCallback;
};

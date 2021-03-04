#include "GameObjects/Components/MeshRenderer.h"

#include <glm/fwd.hpp>

#include "Data/Mesh.h"
#include "Rendering/Renderer.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Camera.h"
#include "GameObjects/Components/Transform.h"
#include "GameSystems/Callbacks.h"
#include "GameSystems/MaterialManager.h"
#include "GameSystems/MeshManager.h"
#include "Rendering/Material.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : Component(false),
                                                             m_renderSceneCallback([this] { Render(); })
{
	this->mesh = mesh;
	this->material = material;
	Renderer::AddRenderSceneCallback(gameObject->id, m_renderSceneCallback);
}

MeshRenderer::MeshRenderer(nlohmann::ordered_json& serializedMeshRenderer) : Component(false), m_renderSceneCallback([this] { Render(); })
{
	Renderer::AddRenderSceneCallback(gameObject->id, m_renderSceneCallback);
	Deserialize(serializedMeshRenderer);
}

MeshRenderer::~MeshRenderer()
{
	Renderer::RemoveRenderSceneCallback(gameObject->id);
}

void MeshRenderer::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

nlohmann::ordered_json MeshRenderer::Serialize()
{
	nlohmann::ordered_json meshRendererSerialized;
	meshRendererSerialized["Mesh"] = mesh->filepath;
	meshRendererSerialized["Material"] = this->material->Serialize();
	return meshRendererSerialized;
}

void MeshRenderer::Deserialize(nlohmann::ordered_json& serializedComponent)
{
	mesh = MeshManager::LoadMesh(serializedComponent["Mesh"]);
	material = MaterialManager::GetMaterial(serializedComponent["Material"]["Shader"]);
}

void MeshRenderer::Render()
{
	if (!m_transform)
	{
		m_transform = gameObject->GetComponentOfType<Transform>();
		if (!m_transform) return;
	}

	const IndexBuffer& meshIndexBuffer = mesh->GetIndexBuffer();

	glm::mat4 _vp = Renderer::MainCamera->ViewProjectMat;

	glm::mat4 mvp = _vp * m_transform->GetModelMatrix();
	
	material->SetUniform("_MVP", mvp);
	material->PrepareForRender();
	Renderer::Draw(mesh->GetVertexArray(), meshIndexBuffer);
}

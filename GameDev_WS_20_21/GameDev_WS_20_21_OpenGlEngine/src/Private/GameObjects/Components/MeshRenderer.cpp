#include "GameObjects/Components/MeshRenderer.h"

#include <glm/fwd.hpp>

#include "Data/Mesh.h"
#include "Rendering/Renderer.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Camera.h"
#include "GameObjects/Components/Transform.h"
#include "Rendering/Material.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material)
{
	this->mesh = mesh;
	this->material = material;
}

MeshRenderer::~MeshRenderer()
{
	
}

void MeshRenderer::Render()
{
	if (!m_transform)
	{
		m_transform = gameObject->GetComponentOfType<Transform>();
		if (!m_transform) return;
	}

	const IndexBuffer& meshIndexBuffer = mesh->GetIndexBuffer();

	glm::mat4 _vp = Renderer::mainCamera->ViewProjectMat;

	glm::mat4 mvp = _vp * m_transform->GetModelMatrix();
	
	material->SetUniform("_MVP", mvp);
	material->PrepareForRender();
	Renderer::Draw(mesh->GetVertexArray(), meshIndexBuffer);
}

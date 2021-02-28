#include "GameObjects/Components/MeshRenderer.h"

#include <glm/gtx/quaternion.hpp>


#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Transform.h"
#include "Rendering/Renderer.h"
#include "Data/Mesh.h"



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

	glm::mat4 scale = glm::scale(glm::mat4(1), m_transform->Scale);
	glm::mat4 rotation = glm::toMat4(m_transform->Rotation);
	glm::mat4 tranlation = glm::translate(glm::mat4(1.0f), m_transform->Location);

	_vp *= scale *  rotation * tranlation;
	
	material->SetUniform("_MVP", _vp);
	material->PrepareForRender();
	Renderer::Draw(mesh->GetVertexArray(), meshIndexBuffer);
}

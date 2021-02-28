#include "GameObjects/Components/MeshRenderer.h"

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

	
}

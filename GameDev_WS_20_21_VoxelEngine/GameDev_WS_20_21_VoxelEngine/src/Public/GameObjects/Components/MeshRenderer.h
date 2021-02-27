#pragma once
#include "Component.h"
#include "Rendering/Material.h"

class VertexArray;
class Mesh;
class Transform;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh mesh, Material material);
	MeshRenderer(Mesh mesh, Material material, VertexArray* vertexArray);
	~MeshRenderer();

	void SetMesh();
	void Render();

public:
	Material* material;
private:
	Transform* m_transform;
};

#pragma once
#include "Component.h"

class Material;
class VertexArray;
class Mesh;
class Transform;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh* mesh, Material* material);
	~MeshRenderer();

	void SetMesh();
	void Render();

	void BindForRender();

public:
	Material* material;
	Mesh* mesh;
private:
	Transform* m_transform;
};
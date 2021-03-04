#include "UiManager.h"



#include "EditorManager.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "GameSystems/GameManager.h"
#include "GameSystems/MaterialManager.h"
#include "GameSystems/MeshManager.h"
#include "imgui/imgui.h"
#include "Rendering/Renderer.h"

EngineCallback UiManager::renderGuiCallback([]() { UiManager::DrawUi(); });

void UiManager::Init()
{
	Renderer::AddRenderGuiCallback(renderGuiCallback);
}

void UiManager::ShutDown()
{
	Renderer::RemoveRenderGuiCallback(renderGuiCallback);
}

void UiManager::DrawUi()
{
	// Any application code here
	ImGui::Text("Hello, world!");

	if (ImGui::Button("Save Scene", ImVec2(100, 20)))
	{
		EditorManager::SaveScene("TestSafe.savefile");
	}

	if (ImGui::Button("Add Monkey", ImVec2(100,20)))
	{
		static uint32_t id = 0;
		GameObject* gameObject = GameManager::AddGameObject("Cube" + std::to_string(id++), glm::vec3(0), glm::vec3(0));
		Mesh* mesh = MeshManager::LoadMesh("../Assets/models/Cube.obj");
		Material* material = MaterialManager::GetMaterial("../Assets/shader/Basic.shader");
		MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);
		gameObject->AddComponent(meshRenderer);

		EditorManager::CurrentlyOpenScene->GameObjects.push_back(gameObject);
	}
}

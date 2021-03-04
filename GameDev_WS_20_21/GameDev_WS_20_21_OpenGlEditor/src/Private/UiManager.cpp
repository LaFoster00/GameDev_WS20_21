#include "UiManager.h"

#include "EditorManager.h"
#include "GameObjects/Components/Camera.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "GameObjects/Components/Transform.h"
#include "GameSystems/GameManager.h"
#include "GameSystems/MaterialManager.h"
#include "GameSystems/MeshManager.h"
#include "imgui/imgui.h"
#include "Rendering/Renderer.h"

EngineCallback UiManager::RenderGuiCallback([]() { UiManager::DrawUi(); });

void UiManager::Init()
{
	Renderer::AddRenderGuiCallback(RenderGuiCallback);
}

void UiManager::ShutDown()
{
	Renderer::RemoveRenderGuiCallback(RenderGuiCallback);
}

void UiManager::DrawUi()
{
	using namespace ImGui;
	{
		
		Begin("Scene");
		{
			ImGui::BeginChild("SceneOutliner", { 0, 0 }, false);
			{
				for (auto object : GameManager::GetGameObjects())
				{
					bool currentlySelected = object == EditorManager::SelectedGameObject;
					if(ImGui::Selectable(object->name.c_str(), currentlySelected) && !currentlySelected)
					{
						EditorManager::SelectedGameObject = object;
					}
				}
				
			}
			ImGui::EndChild();
		}
		End();
		
		// Any application code here
		ImGui::Text("Hello, world!");

		ImGui::SliderFloat3("Translation Camera", &Renderer::MainCamera->gameObject->GetComponentOfType<Transform>()->Location.x, -5, 5);

		if (ImGui::Button("Save Scene", ImVec2(100, 20)))
		{
			EditorManager::SaveScene("TestSafe.savefile");
		}

		if (ImGui::Button("Load Scene", ImVec2(100, 20)))
		{
			EditorManager::LoadScene("TestSafe.savefile");
		}

		if (ImGui::Button("Add Monkey", ImVec2(100, 20)))
		{
			static uint32_t id = 0;
			GameObject* gameObject = GameManager::AddGameObject("Cube" + std::to_string(id++), glm::vec3(0), glm::vec3(0));
			MeshRenderer* meshRenderer = new MeshRenderer();
			Mesh* mesh = MeshManager::LoadMesh("../Assets/models/Monkey.obj");
			meshRenderer->SetMesh(mesh);
			Material* material = MaterialManager::GetMaterial("../Assets/shader/Basic.shader");
			meshRenderer->SetMaterial(material);

			gameObject->AddComponent(meshRenderer);
		}
	}
}

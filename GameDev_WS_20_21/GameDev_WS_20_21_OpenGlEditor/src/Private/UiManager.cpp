#include "UiManager.h"

#include "EditorManager.h"
#include "GameObjects/Components/Camera.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "GameObjects/Components/Transform.h"
#include "GameSystems/GameManager.h"
#include "GameSystems/MaterialManager.h"
#include "GameSystems/MeshManager.h"
#include "imgui/imgui.h"
#include "Rendering/Material.h"
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
			BeginChild("SceneOutliner", { 0, 0 }, false);
			{
				for (auto object : GameManager::GetGameObjects())
				{
					bool currentlySelected = object == EditorManager::SelectedGameObject;
					if(Selectable(object->name.c_str(), currentlySelected) && !currentlySelected)
					{
						EditorManager::SelectedGameObject = object;
					}
				}
				
			}
			ImGui::EndChild();
		}
		End();

		/// <summary>
		/// This should be managed via per component draw calls giving the possiblity to just go through all components and call DrawInspector or something like that
		/// But at the same time that would probably defeat the purpose of seperating editor and Game engine so im not 100% sure about how to approach this best
		/// </summary>
		Begin("Inspector");
		{
			
			if (EditorManager::SelectedGameObject)
			{
				BeginChild("Transform");
				{
					Transform* transform = EditorManager::SelectedGameObject->GetComponentOfType<Transform>();
					DragFloat3("Location", &transform->Location.x);
					DragFloat3("Rotation", &transform->Rotation.x);
					DragFloat3("Scale", &transform->Scale.x);
				}
				EndChild();

				if (EditorManager::SelectedGameObject->GetComponentOfType<Camera>())
				{
					BeginChild("Camera");
					{
						Camera* camera = EditorManager::SelectedGameObject->GetComponentOfType<Camera>();
						DragFloat("Fov", &camera->cameraSettings.fov);
						DragFloat("NearPlane", &camera->cameraSettings.nearPlane);
						DragFloat("FarPlane", &camera->cameraSettings.farPlane);
					}
					EndChild();
				}

				if (EditorManager::SelectedGameObject->GetComponentOfType<MeshManager>())
				{
					BeginChild("MeshRenderer");
					{
						MeshRenderer* meshRenderer = EditorManager::SelectedGameObject->GetComponentOfType<MeshRenderer>();
						std::string MeshLabel = "Mesh used :" + meshRenderer->mesh->filepath;
						ImGui::LabelText(MeshLabel.c_str(), "");
					}
				}
			}
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

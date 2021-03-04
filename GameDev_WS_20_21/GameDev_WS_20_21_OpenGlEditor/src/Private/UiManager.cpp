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
		Begin("Menu");
		{
			{
				static char NewObjectName[100] = "New Game Object";
				static char MeshImportFilepath[100] = "Assets/models/Cube.obj";
				ImGui::InputText("Game Object Name", NewObjectName, 100);
				ImGui::InputText("Mesh Path", MeshImportFilepath, 100);
				if (Button("Create new object with Mesh", { GetWindowContentRegionWidth(), 20 }))
				{
					GameObject* go = GameManager::AddGameObject(NewObjectName, glm::vec3(0), glm::vec3(0));
					Mesh* mesh = MeshManager::LoadMesh(MeshImportFilepath);
					Material* material = MaterialManager::GetDefaultMaterial();
					MeshRenderer* meshRenderer = new MeshRenderer();
					meshRenderer->mesh = mesh;
					meshRenderer->material = material;

					go->AddComponent(meshRenderer);
					
				}
			}

			{
				static char LoadSceneFilepath[100] = "Assets/Maps/Default.savefile";
				ImGui::InputText("Load Scene File Path", LoadSceneFilepath, 100);
				if (Button("Load Scene", { GetWindowContentRegionWidth(), 20 }))
				{
					EditorManager::LoadScene(LoadSceneFilepath);
				}
			}

			{
				static char SaveSceneFilepath[100] = "Assets/Maps/Default.savefile";
				ImGui::InputText("Save Scene File Path", SaveSceneFilepath, 100);
				if (Button("Save Scene", { GetWindowContentRegionWidth(), 20 }))
				{
					EditorManager::SaveScene(SaveSceneFilepath);
				}
			}
		}
		End();
		
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
			bool destroyObject = false;
			if (EditorManager::SelectedGameObject)
			{
				if (Button("Delete", { GetWindowContentRegionWidth(), 30 }))
				{
					destroyObject = true;
				}
			
				BeginChild("Transform", { ImGui::GetWindowContentRegionWidth(), 30 * 3 });
				{
					static char bufferName[100] = "";
					strcpy_s(bufferName, EditorManager::SelectedGameObject->name.c_str());
					if (InputText("Name", bufferName, 100))
					{
						EditorManager::SelectedGameObject->name = bufferName;
					}
				}
				EndChild();
				
				BeginChild("Transform", { ImGui::GetWindowContentRegionWidth(), 30 * 3 } );
				{
					Transform* transform = EditorManager::SelectedGameObject->GetComponentOfType<Transform>();
					DragFloat3("Location", &transform->Location.x);
					DragFloat3("Rotation", &transform->Rotation.x);
					DragFloat3("Scale", &transform->Scale.x);
				}
				EndChild();

				if (EditorManager::SelectedGameObject->GetComponentOfType<Camera>())
				{
					BeginChild("Camera", { ImGui::GetWindowContentRegionWidth(), 30 * 3 } );
					{
						Camera* camera = EditorManager::SelectedGameObject->GetComponentOfType<Camera>();
						DragFloat("Fov", &camera->cameraSettings.fov);
						DragFloat("NearPlane", &camera->cameraSettings.nearPlane);
						DragFloat("FarPlane", &camera->cameraSettings.farPlane);
					}
					EndChild();
				}

				if (EditorManager::SelectedGameObject->GetComponentOfType<MeshRenderer>())
				{
					BeginChild("MeshRenderer", { ImGui::GetWindowContentRegionWidth(), 30 * 6 } );
					{
						MeshRenderer* meshRenderer = EditorManager::SelectedGameObject->GetComponentOfType<MeshRenderer>();

						//Mesh Outliner
						{
							LabelText("Mesh Used: ", meshRenderer->mesh ? meshRenderer->mesh->filepath.c_str() : "None");

							static char filepathBuffer[100] = "Assets/models/Monkey.obj";
							ImGui::InputText("New Mesh", filepathBuffer, 100);
							if (Button("Replace with New Mesh", { GetWindowContentRegionWidth() , 20 }))
							{
								meshRenderer->mesh = MeshManager::LoadMesh(filepathBuffer);
							}
						}

						//Material Outliner
						{
							Shader* shader = meshRenderer->material->shader;
							LabelText("Shader used in Material: ", shader ? shader->GetFilepath().c_str() : "None");

							static char shaderFilepathBuffer[100] = "Assets/shader/Basic.shader";
							ImGui::InputText("New Shader", shaderFilepathBuffer, 100);
							if (Button("Replace with New Shader", { GetWindowContentRegionWidth(), 20 }))
							{
								meshRenderer->material = MaterialManager::GetMaterial(shaderFilepathBuffer);
							}

						}
					}
					EndChild();

				}
			}
			if (destroyObject)
			{
				GameManager::DestroyGameObject(EditorManager::SelectedGameObject);
				EditorManager::SelectedGameObject = nullptr;
			}
		}
		End();
	}
}

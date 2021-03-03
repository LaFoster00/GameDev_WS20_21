#include "UiManager.h"



#include "EditorManager.h"
#include "imgui/imgui.h"
#include "Rendering/Renderer.h"

EngineCallback UiManager::renderGuiCallback([]() { UiManager::DrawUi(); });

void UiManager::Init()
{
	Renderer::AddRenderGuiCallback(renderGuiCallback.id, renderGuiCallback);
}

void UiManager::ShutDown()
{
	Renderer::RemoveRenderGuiCallback(renderGuiCallback.id);
}

void UiManager::DrawUi()
{
	// Any application code here
	ImGui::Text("Hello, world!");

	if (ImGui::Button("Save Scene", ImVec2(100, 20)))
	{
		EditorManager::SaveScene("TestSafe.savefile");
	}
}

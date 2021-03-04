#pragma once
#include <vector>

#include "GameSystems/Callbacks.h"

struct SceneObject;



class UiManager
{
public:
	static void Init();
	static void ShutDown();
	
	static void DrawUi();
private:
	static EngineCallback RenderGuiCallback;
};

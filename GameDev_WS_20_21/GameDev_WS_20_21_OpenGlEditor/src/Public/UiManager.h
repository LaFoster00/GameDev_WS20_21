#pragma once
#include "GameSystems/Callbacks.h"

class UiManager
{
public:
	static void Init();
	static void ShutDown();
	
	static void DrawUi();
private:
	static EngineCallback renderGuiCallback;
};

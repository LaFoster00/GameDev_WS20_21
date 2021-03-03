#include "Serialization/EngineArchive.h"

#include <fstream>

EngineArchive* EngineArchive::Instance;

EngineArchive::EngineArchive(const std::string filepath)
{
	Filepath = filepath;
}

void EngineArchive::LoadEngineConfig(const std::string filepath)
{
	if (!Instance)
	{
		Instance = new EngineArchive(filepath);
	}

	std::ifstream file(filepath);
	if (file.is_open())
	{
		JsonInputArchive input(filepath);

		input.Serialize(Instance->WindowSizeX, "WindowSizeX");
		input.Serialize(Instance->WindowSizeY, "WindowSizeY");
		input.Serialize(Instance->WindowName, "WindowName");
		input.Serialize(Instance->VSync, "VSync");
		input.Serialize(Instance->glMajor, "GlMajor");
		input.Serialize(Instance->glMinor, "GlMinor");
	}else
	{
		SaveEngineConfig();
	}

}

void EngineArchive::SaveEngineConfig()
{
	if (!Instance) return;

	JsonOutputArchive output(Instance->Filepath);
	
	output.Serialize(Instance->WindowSizeX, "WindowSizeX");
	output.Serialize(Instance->WindowSizeY, "WindowSizeY");
	output.Serialize(Instance->WindowName, "WindowName");
	output.Serialize(Instance->VSync, "VSync");
	output.Serialize(Instance->glMajor, "GlMajor");
	output.Serialize(Instance->glMinor, "GlMinor");
}

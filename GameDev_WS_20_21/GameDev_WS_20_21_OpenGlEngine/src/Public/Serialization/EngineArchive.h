#pragma once
#include "JsonArchive.h"

class EngineArchive
{
public:
	EngineArchive() = delete;
	EngineArchive(const std::string filepath);

	static EngineArchive* Get()
	{
		return Instance;
	}
	static void LoadEngineConfig(const std::string filepath);
	static void SaveEngineConfig();
public:
	uint32_t WindowSizeX = 640 * 2; 
	uint32_t WindowSizeY = 480 * 2;
	std::string WindowName = "OpenGlEngine";
	bool VSync = false;
	uint32_t glMajor = 4;
	uint32_t glMinor = 1;
private:

	std::string Filepath;
	
	static EngineArchive* Instance;
};
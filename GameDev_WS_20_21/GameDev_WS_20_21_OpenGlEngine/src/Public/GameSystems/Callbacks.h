#pragma once
#include <functional>


struct EngineCallback
{
	uint32_t id;
	std::function<void()> callback;

	EngineCallback() = delete;
	EngineCallback(std::function<void()> callback)
	{
		static uint32_t ids = 0;
		id = ++ids;
		this->callback = callback;
	}
};

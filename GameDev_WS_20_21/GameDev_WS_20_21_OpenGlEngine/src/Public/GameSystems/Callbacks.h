#pragma once

template<typename...Args>
struct EngineCallback
{
	uint32_t id;
	void(*Callback)(Args ...);

	EngineCallback() = delete;
	EngineCallback(void(*C)(Args ...))
	{
		static uint32_t ids = 0;
		id = ++ids;
		Callback = C;
	}
};
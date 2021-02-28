#pragma once
#include <iostream>

class Time
{
public:
	static void UpdateGameTime()
	{
		_currentFrameTick = clock();
		DeltaTime = static_cast<double>(_currentFrameTick - _lastFrameTick) / CLOCKS_PER_SEC;
		_lastFrameTick = clock();
	}
	
	static double DeltaTime;

private:
	static clock_t _lastFrameTick;
	static clock_t _currentFrameTick;
};
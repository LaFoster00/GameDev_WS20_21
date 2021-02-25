#include "EngineTime.h"

double Time::DeltaTime = 0;
clock_t Time::_lastFrameTick = 0;
clock_t Time::_currentFrameTick = 0;
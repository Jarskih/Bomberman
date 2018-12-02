#pragma once
#include <SDL.h>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;
	Uint32 getTicks();
	void start();
private:
	bool m_isStarted = false;
	bool m_isPaused = false;
	Uint32 m_pause = 0;
	Uint32 m_start = 0;
};


#include "Timer.h"


Uint32 Timer::getTicks() const
{

	Uint32 time = 0;

	if (m_isStarted)
	{
		if (m_isPaused)
			time = m_pause;
	}
	else
	{
		time = SDL_GetTicks() - m_start;
	}
	return time;
}

void Timer::start()
{
	//Start the timer
	m_isStarted = true;

	//Unpause the timer
	m_isPaused = false;

	//Get the current clock time
	m_start = SDL_GetTicks();
	m_pause = 0;
}

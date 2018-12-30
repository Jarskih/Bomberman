#include "Timer.h"


Uint32 Timer::getTicks() const
{

	Uint32 time = 0;

	if (m_isPaused) {
		time = m_pause;
	}
	else {
		time = SDL_GetTicks() - m_start;
	}
	return time;
}

Uint32 Timer::getSeconds() const
{
	Uint32 seconds = m_roundTime - getTicks() / 1000 - getMinutes() * 60;

	return seconds;
}

Uint32 Timer::getMinutes() const
{
	Uint32 minutes = (m_roundTime - getTicks() / 1000) / 60;

	return minutes;
}

int Timer::getTimeLeft() const
{
	auto timeLeft = m_roundTime - getTicks() / 1000;
	return timeLeft;
}

void Timer::start()
{
	m_isStarted = true;
	m_isPaused = false;
	m_start = SDL_GetTicks();
	m_pause = 0;
}

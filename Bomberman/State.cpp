#include "State.h"

void State::changeScene(int newScene)
{
	m_scene = newScene;
}

void State::sceneTransition()
{
	switch (m_scene)
	{
	case MENU:
		changeScene(LEVEL_INTRO);
		break;
	case LEVEL_INTRO:
		changeScene(LEVEL);
		break;
	case LEVEL:
		break;
	case DEFEAT:
		changeScene(MENU);
		break;
	default:
		break;
	}
}

void State::incrementScore(int addedScore)
{
	m_score += addedScore;
}

void State::incrementLives()
{
	m_lives++;
}

void State::decrementLives()
{
	m_lives--;
}


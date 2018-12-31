#include "State.h"

void State::changeScene(int newScene)
{
	scene = newScene;
}

void State::sceneTransition()
{
	switch (scene)
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
	score += addedScore;
}

void State::incrementLives()
{
	lives++;
}

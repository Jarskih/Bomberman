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
		scene = LEVEL_INTRO;
		break;
	case LEVEL_INTRO:
		scene = LEVEL;
		break;
	case LEVEL:
		break;
	case DEFEAT:
		scene = MENU;
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

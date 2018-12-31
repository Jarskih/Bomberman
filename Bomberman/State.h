#pragma once
#include "GameRules.h"

struct State
{
	enum Scenes
	{
		MENU,
		LEVEL_INTRO,
		LEVEL,
		DEFEAT

	};
	State() {};
	int score = 0;
	int players = NUMBER_OF_PLAYERS;
	int lives = STARTING_LIVES;
	int scene = MENU;

	void changeScene(int newScene);
	void incrementScore(int addedScore);
	void incrementLives();
	void sceneTransition();
};

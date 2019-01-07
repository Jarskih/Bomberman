#pragma once
#include "Config.h"

struct State
{
	enum Scenes
	{
		MENU,
		LEVEL_INTRO,
		LEVEL,
		DEFEAT

	};
	State() = default;
	int m_score = 0;
	int m_players = Config::NUMBER_OF_PLAYERS;
	int m_scene = MENU;
	int m_lives = Config::STARTING_LIVES;

	void changeScene(int newScene);
	void incrementScore(int addedScore);
	void incrementLives();
	void decrementLives();
	void sceneTransition();
};

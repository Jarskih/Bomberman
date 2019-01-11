#pragma once
#include "Config.h"
#include "Helpers.h"
#include "GUIArrow.h"

class GUIArrow;

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
	int m_enemies = Config::NUMBER_OF_ENEMIES;
	int m_lives = Config::STARTING_LIVES;
	bool m_debug = false;
	int m_level = 1;
	bool m_level_cleared = false;
	bool m_enemies_dead = false;

	void changeScene(int newScene);
	void incrementScore(int addedScore);
	void incrementLives();
	void decrementLives();
	void sceneTransition(sp<GUIArrow> &arrow);
	void toggleDebug();
	void goToMenu();
	void nextLevel();
};

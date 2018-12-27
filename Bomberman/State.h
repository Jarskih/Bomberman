#pragma once
#include <vector>
#include "Actor.h"

struct State
{
public:
	State(int players) : m_players(players) {};
	int m_score = 0;
	int m_players = 1;
	std::vector<Actor> game_objects = {};
};

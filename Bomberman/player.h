#pragma once
#include <SDL.h>
#include "GameRules.h"
#include <vector>
#include "Block.h"
#include "Helpers.h"

class Player {
public:
	bool isAlive = true;
	bool moving = false;
	int speed = 3;
	float posX = BLOCK_WIDTH + BLOCK_WIDTH / 2;
	float posY = BLOCK_HEIGHT / 2;
	int flamePower = 1;
	int maxBombs = 1;
	int bombsDropped = 0;

	float speed_x = 0;
	float speed_y = 0;

	Player() = default;
	~Player() = default;

	enum states { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT };
	int state = IDLE_DOWN;
	SDL_Rect collider = { 0, 0, PLAYER_WIDTH / 3, PLAYER_HEIGHT / 3 };
	SDL_Rect windowRect = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect textureRect = { 0, 0 };
	SDL_Texture* texture = nullptr;

	SDL_Texture* loadTexture(SDL_Renderer* renderer);
	const char* Player::GetSprite();
	void handleEvent(SDL_Event& event);
	void playerController();
	void movePlayer(std::vector<sp<Block>> blocks);
	void render(SDL_Renderer* renderer);
	void DropBomb();
};

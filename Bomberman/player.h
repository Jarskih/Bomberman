#pragma once
#include <SDL.h>
#include "GameRules.h"
#include <vector>
#include "Block.h"
#include "Helpers.h"
#include "Map.h"
#include "Bomb.h"

static const int PLAYER_WIDTH = 100;
static const int PLAYER_HEIGHT = 80;

class Player {
public:
	bool isAlive = true;
	bool moving = false;
	int speed = 3;
	float posX = BLOCK_WIDTH + BLOCK_WIDTH / 2;
	float posY = BLOCK_HEIGHT / 2;
	int flamePower = 2;
	int maxBombs = 1;

	float speed_x = 0;
	float speed_y = 0;

	Player(SDL_Renderer* renderer) : m_renderer(renderer) {};
	~Player() = default;

	std::vector<sp<Bomb>> bombs = {};
	enum states { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT };
	int state = IDLE_DOWN;
	SDL_Rect collider = { 0, 0, PLAYER_WIDTH / 3, PLAYER_HEIGHT / 3 };
	SDL_Rect windowRect = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect textureRect = { 0, 0 };
	SDL_Texture* texture = nullptr;

	void update(const sp<Map> &map);
	void checkBombs();
	SDL_Texture* loadTexture() const;
	const char* Player::GetSprite() const;
	/* void handleEvent(SDL_Event& event); */
	void playerController(sp<Map> map);
	void movePlayer(std::vector<sp<Block>> blocks);
	void renderBombs(const sp<Map> &map);
	void render();
	void dropBomb(const sp<Map> &map);
private:
	SDL_Renderer* m_renderer = nullptr;
};

#pragma once
#include <SDL.h>
#include <vector>
#include "Block.h"
#include "Helpers.h"
#include "Map.h"
#include "Bomb.h"

static const int PLAYER_WIDTH = 100;
static const int PLAYER_HEIGHT = 80;

class Player {
public:
	Player(SDL_Renderer* renderer) : m_renderer(renderer) {};
	~Player() = default;
	void update();
	void render();
	void handleEvent(SDL_Event& event);
	void die();
private:
	std::vector<sp<Bomb>> checkBombs();
	void playerController();
	void movePlayer();
	void renderBombs();
	void dropBomb();
	void animate();
public:
	bool isAlive = true;
	bool moving = false;
	int speed = 3;
	float posX = BLOCK_WIDTH + BLOCK_WIDTH / 2.f;
	float posY = BLOCK_HEIGHT / 2.f;
	int flamePower = 2;
	int maxBombs = 3;
	float speed_x = 0;
	float speed_y = 0;
	std::vector<sp<Bomb>> bombs = {};
	int bombsDropped = 0;
	enum states { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT };
	int state = IDLE_DOWN;
	SDL_Rect collider = { 0, 0, PLAYER_WIDTH / 3, PLAYER_HEIGHT / 3 };
private:
	SDL_Texture* loadTexture() const;
	const char* Player::GetSprite() const;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect windowRect = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect textureRect = { 0, 0 };
	SDL_Texture* texture = nullptr;
};

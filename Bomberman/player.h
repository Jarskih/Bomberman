#pragma once
#include <SDL.h>
#include <vector>
#include "Helpers.h"
#include "Bomb.h"
#include "State.h"
#include "Service.h"

class Bomb;

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
	bool moving = false;
	int speed = 3;
	int posX = BLOCK_WIDTH + BLOCK_WIDTH / 2.0f;
	int posY = BLOCK_HEIGHT + BLOCK_HEIGHT / 2.0f;
	int flamePower = 1;
	int maxBombs = 1;
	bool isDead = false;
	int lives = Service<State>::Get()->lives;
	float speed_x = 0;
	float speed_y = 0;
	std::vector<sp<Bomb>> bombs = {};
	int bombsDropped = 0;
	enum states { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT, DEAD };
	int state = IDLE_DOWN;
	int oldState;
	SDL_Rect collider = { 0, 0, PLAYER_WIDTH / 3, PLAYER_HEIGHT / 3 };
private:
	std::string textureName = "playerMoveDown";
	SDL_Texture* loadTexture();
	// const char* Player::GetSprite() const;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect windowRect = { 0, 0,  PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect textureRect = { 0, 0, 0, 0 };
	SDL_Texture* texture = nullptr;
	int frame = 0;
	Uint32 timeDied;
	Uint32 oldTime = 0;
	Uint32 delayPerFrame = 200;
};

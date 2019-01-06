#pragma once
#include <SDL.h>
#include <vector>
#include "Helpers.h"
#include "Bomb.h"
#include "State.h"
#include "Service.h"
#include "Entity.h"

class Bomb;

class Player : public Entity {
public:
	Player(SDL_Renderer* renderer) : m_renderer(renderer) {
		posX = BLOCK_WIDTH + BLOCK_WIDTH / 2.0f;
		posY = BLOCK_HEIGHT + BLOCK_HEIGHT / 2.0f;
		m_type = PLAYER;
		m_active = true;
		m_visible = true;
		m_collider = { 0, 0, PLAYER_WIDTH / 3, PLAYER_HEIGHT / 3 };
		m_windowRect = { 0, 0,  PLAYER_WIDTH, PLAYER_HEIGHT };
		m_textureRect = { 0, 0, 0, 0 };
		state = IDLE_DOWN;
		speed_x = 0;
		speed_y = 0;
	};
	Player() = delete;
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
	//int posX = BLOCK_WIDTH + BLOCK_WIDTH / 2.0f;
	//int posY = BLOCK_HEIGHT + BLOCK_HEIGHT / 2.0f;
	int flamePower = 1;
	int maxBombs = 1;
	bool isDead = false;
	int m_lives = Service<State>::Get()->lives;
	std::vector<sp<Bomb>> bombs = {};
	int bombsDropped = 0;
	int oldState;
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
	Uint32 delayPerFrame = 100;
};

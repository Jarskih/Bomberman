#pragma once
#include <SDL.h>

class Player {
public:
	bool isAlive = true;
	int speed = 1;
	int posX = 200;
	int posY = 200;

	int speed_x = 0;
	int speed_y = 0;

	Player();
	enum states { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT };
	int state = DOWN;
	SDL_Rect collider = { 60, 60, 30, 30 };
	SDL_Rect windowRect = { 0, 0, 60, 60 };
	SDL_Rect textureRect = { 0, 0 };
	SDL_Texture* texture;
	SDL_Texture* loadTexture(SDL_Renderer* renderer);
	const char* Player::GetSprite();
	void handleEvent(SDL_Event& event);
	void movePlayer(SDL_Rect& wall);
	void render(SDL_Renderer* renderer);
	void animate();
};

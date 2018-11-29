#pragma once
#include <SDL.h>

class Player {
public:
	bool isAlive = true;
	int speed = 1;
	int posX = 0;
	int posY = 0;

	int speed_x = 0;
	int speed_y = 0;

	Player();
	SDL_Rect windowRect = { 0, 0, 50, 50 };
	SDL_Rect textureRect = { 0, 0 };
	SDL_Texture* texture;
	SDL_Texture* loadTexture(SDL_Renderer* renderer);
	void handleEvent(SDL_Event& event);
	void movePlayer();
	void render(SDL_Renderer* renderer);
	void animate();
};

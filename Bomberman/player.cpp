#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include "GameRules.h"

Player::Player() {
}

SDL_Texture* Player::loadTexture(SDL_Renderer* renderer) {
	SDL_Texture* whitePlayer = NULL;
	SDL_Surface* surface = IMG_Load("img/32x288_white.png");
	if (!surface) {
		std::cout << "Cant load player" << std::endl;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void Player::handleEvent(SDL_Event& event) {
	//If a key was pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			speed_y -= speed;
			break;
		case SDLK_DOWN:
			speed_y += speed;
			break;
		case SDLK_LEFT:
			speed_x -= speed;
			break;
		case SDLK_RIGHT:
			speed_x += speed;
			break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: speed_y += speed; break;
		case SDLK_DOWN: speed_y -= speed; break;
		case SDLK_LEFT: speed_x += speed; break;
		case SDLK_RIGHT: speed_x -= speed; break;
		}
	}
}

void Player::movePlayer() {
	//Move the dot left or right
	posX += speed_x;
	windowRect.x = posX;

	//If the dot went too far to the left or right
	if ((posX < 0) || (posX + PLAYER_WIDTH > SCREEN_WIDTH))
	{
		//Move back
		posX -= speed_x;
		windowRect.x = posX;
	}
	//Move the dot up or down
	posY += speed_y;
	windowRect.y = posY;

	//If the dot went too far up or down
	if ((posY < 0) || (posY + PLAYER_HEIGHT > SCREEN_HEIGHT))
	{
		//Move back
		posY -= speed_y;
		windowRect.y = posY;
	}
}

void Player::render(SDL_Renderer* renderer) {

	texture = loadTexture(renderer);

	SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);

	textureRect.h /= 9;

	SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);
}

void Player::animate() {
	int totalFrames = 9;
	int delayPerFrame = 100;
	int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
	textureRect.y = frame * textureRect.h;
}

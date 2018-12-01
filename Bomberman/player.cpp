#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include "GameRules.h"
#include "Helpers.h"

const char* Player::GetSprite() {
	switch (state) {
	case DOWN:
		return "img/player_move_down.png";
		break;
	case UP:
		return "img/player_move_up.png";
		break;
	case RIGHT:
		return "img/player_move_right.png";
		break;
	case LEFT:
		return "img/player_move_left.png";
		break;
	default:
		return "img/player_move_down.png";
		break;
	}
}

Player::Player() {
}

SDL_Texture* Player::loadTexture(SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;
	const char* sprite = GetSprite();

	SDL_Surface* surface = IMG_Load(sprite);
	if (!surface) {
		std::cout << "Cant load player" << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
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
			state = UP;
			break;
		case SDLK_DOWN:
			speed_y += speed;
			state = DOWN;
			break;
		case SDLK_LEFT:
			speed_x -= speed;
			state = LEFT;
			break;
		case SDLK_RIGHT:
			speed_x += speed;
			state = RIGHT;
			break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: speed_y += speed;
			state = IDLE_UP;
			break;
		case SDLK_DOWN: speed_y -= speed;
			state = IDLE_DOWN;
			break;
		case SDLK_LEFT: speed_x += speed;
			state = IDLE_LEFT;
			break;
		case SDLK_RIGHT: speed_x -= speed;
			state = IDLE_RIGHT;
			break;
		}
	}
}

void Player::movePlayer(SDL_Rect& wall) {

	posX += speed_x;
	windowRect.x = posX;
	collider.x = posX;

	if ((posX < 0) || (posX + PLAYER_WIDTH > SCREEN_WIDTH) || isOutOfGamearea(collider, wall))
	{
		//Move back
		posX -= speed_x;
		windowRect.x = posX;
		collider.x = posX;
	}

	posY += speed_y;
	windowRect.y = posY;
	collider.y = posY;

	if ((posY < 0) || (posY + PLAYER_HEIGHT > SCREEN_HEIGHT) || isOutOfGamearea(collider, wall))
	{
		//Move back
		posY -= speed_y;
		windowRect.y = posY;
		collider.y = posY;
	}
}

void Player::render(SDL_Renderer* renderer) {
	int totalFrames = 1;
	bool moving = false;

	switch (state) {
	case UP:
		totalFrames = 7;
		moving = true;
		break;
	case IDLE_UP:
		totalFrames = 7;
		moving = false;
		break;
	case DOWN:
		totalFrames = 8;
		moving = true;
		break;
	case IDLE_DOWN:
		totalFrames = 8;
		moving = false;
		break;
	case LEFT:
		totalFrames = 8;
		moving = true;
		break;
	case IDLE_LEFT:
		totalFrames = 8;
		moving = false;
		break;
	case RIGHT:
		totalFrames = 9;
		moving = true;
		break;
	case IDLE_RIGHT:
		totalFrames = 9;
		moving = false;
		break;
	default:
		break;
	}

	if (moving) {
		int delayPerFrame = 100;
		int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
		textureRect.y = frame * textureRect.h;

		SDL_DestroyTexture(texture);
		texture = loadTexture(renderer);

		SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);

		textureRect.h /= totalFrames;
	}

	SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);
}

void Player::animate() {
}

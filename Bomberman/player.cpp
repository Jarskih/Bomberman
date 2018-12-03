#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include "GameRules.h"
#include "Helpers.h"
#include "Bomb.h"


const char* Player::GetSprite() {
	switch (state) {
	case DOWN:
		return "img/player_move_down.png";
		break;
	case IDLE_DOWN:
		return "img/player_move_down.png";
		break;
	case UP:
		return "img/player_move_up.png";
		break;
	case IDLE_UP:
		return "img/player_move_up.png";
		break;
	case RIGHT:
		return "img/player_move_right.png";
		break;
	case IDLE_RIGHT:
		return "img/player_move_right.png";
		break;
	case LEFT:
		return "img/player_move_left.png";
		break;
	case IDLE_LEFT:
		return "img/player_move_left.png";
		break;
	default:
		return "error";
		break;
	}
}

SDL_Texture* Player::loadTexture(SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;
	const char* sprite = GetSprite();

	if (sprite == "error") {
		std::cout << "Error loading sprite" << std::endl;
	}

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
		case SDLK_SPACE:
			DropBomb();
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		moving = false;
		if (event.key.repeat == 0) {
		}
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
		default:
			break;
		}
	}
}

void Player::playerController()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		state = UP;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		state = DOWN;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		state = LEFT;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		state = RIGHT;
	}
	else
	{
		if (state == UP)
		{
			state = IDLE_UP;
		}
		if (state == DOWN)
		{
			state = IDLE_DOWN;
		}
		if (state == LEFT)
		{
			state = IDLE_LEFT;
		}
		if (state == RIGHT)
		{
			state = IDLE_RIGHT;
		}
		moving = false;
	}
}

void Player::movePlayer(SDL_Rect& wall) {
	switch (state) {
	case UP:
		posY -= speed;
		moving = true;
		break;
	case IDLE_UP:
		moving = false;
		break;
	case DOWN:
		posY += speed;
		moving = true;
		break;
	case IDLE_DOWN:
		moving = false;
		break;
	case LEFT:
		posX -= speed;
		moving = true;
		break;
	case IDLE_LEFT:
		moving = false;
		break;
	case RIGHT:
		posX += speed;
		moving = true;
		break;
	case IDLE_RIGHT:
		moving = false;
		break;
	default:
		break;
	}
	windowRect.x = posX;
	collider.x = posX + PLAYER_WIDTH / 4;
	windowRect.y = posY;
	collider.y = posY + PLAYER_HEIGHT / 2;

	if (checkCollision(collider, wall))
	{
		posX -= speed;
		windowRect.x = posX;
		collider.x = posX + PLAYER_WIDTH / 4;

		posY -= speed;
		windowRect.y = posY;
		collider.y = posY + PLAYER_HEIGHT / 2;
	}
}

void Player::render(SDL_Renderer* renderer) {
	int totalFrames = 8;

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
	}


	SDL_DestroyTexture(texture);
	texture = loadTexture(renderer);

	SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;

	SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);
}

void Player::DropBomb() {
	auto bomb = mksp<Bomb>(flamePower, posX, posY);
	bombsDropped++;
}

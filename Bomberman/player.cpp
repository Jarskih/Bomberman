#include "player.h"
#include <SDL_image.h>
#include <iostream>
#include "GameRules.h"
#include <memory>
#include "Helpers.h"
#include "Bomb.h"
#include "Block.h"
#include "Map.h"

void Player::update(const sp<Map> &map)
{
	playerController(map);
	movePlayer(map->tileSet);
	checkBombs();
}

void Player::checkBombs()
{
	for (const auto& bomb : bombs)
	{
		if (bomb->isExploded)
		{
			bombs.erase(bombs.begin());
		}
	}
}

const char* Player::GetSprite() const
{
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

SDL_Texture* Player::loadTexture() const
{
	SDL_Texture* texture = nullptr;
	const char* sprite = GetSprite();

	if (sprite == "error") {
		std::cout << "Error loading sprite" << std::endl;
	}

	SDL_Surface* surface = IMG_Load(sprite);
	if (!surface) {
		std::cout << "Cant load player" << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
/*
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
*/
void Player::playerController(sp<Map> map)
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
	else if (currentKeyStates[SDL_SCANCODE_SPACE])
	{
		dropBomb(map);
	}
	else {
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

void Player::movePlayer(std::vector<sp<Block>> blocks) {
	const int oldX = posX;
	const int oldY = posY;

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
	collider.x = posX + PLAYER_WIDTH / 3.f;
	windowRect.y = posY;
	collider.y = posY + PLAYER_HEIGHT / 2.f;

	for (const auto& block : blocks)
	{
		if (block->blockType != GRASS && checkCollision(collider, block->collider))
		{
			posX = oldX;
			windowRect.x = posX;
			collider.x = posX + PLAYER_WIDTH / 3.f;

			posY = oldY;
			windowRect.y = posY;
			collider.y = posY + PLAYER_HEIGHT / 2.f;
		}
	}
}

void Player::renderBombs(const sp<Map> &map)
{
	for (const auto& bomb : bombs)
	{
		bomb->render(m_renderer);
	}
}

void Player::render(const sp<Map> &map) {

	renderBombs(map);
	animate(map);

	// Debug
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(m_renderer, &collider);
}

void Player::animate(const sp<Map> &map)
{
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

	SDL_DestroyTexture(texture);
	texture = loadTexture();


	if (moving) {
		const int delayPerFrame = 100;
		const int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
		textureRect.y = frame * textureRect.h;
	}

	SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;

	SDL_RenderCopy(m_renderer, texture, &textureRect, &windowRect);
}

void Player::dropBomb(const sp<Map> &map) {
	if (maxBombs > bombs.size())
	{
		//std::cout << "Player X: " << m_pos_x << " Player Y: " << m_pos_y << std::endl;
		const std::pair<int, int> currentBlockIndex = getCurrentBlock(posX, posY);
		//std::cout << "Current block X: " << currentBlockIndex.first << " Current block Y: " << currentBlockIndex.second << std::endl;

		std::pair<int, int> blockCenter = getBlockCenter(currentBlockIndex.first, currentBlockIndex.second);
		//std::cout << "Block center X: " << blockCenter.first << " Block Center Y: " << blockCenter.second << std::endl;


		std::pair <int, int> testIndex = getCurrentBlock(blockCenter.first, blockCenter.second);
		//std::cout << "Test index X: " << testIndex.first << " Block index Y: " << testIndex.second << std::endl;

		const auto bomb = makesp<Bomb>(flamePower, blockCenter.first, blockCenter.second, map);
		bomb->load_textures(m_renderer, "bomb");

		bombs.emplace_back(bomb);
	}
}

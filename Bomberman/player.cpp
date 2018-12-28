#include "player.h"
#include <SDL_image.h>
#include <iostream>
#include "GameRules.h"
#include <memory>
#include "Helpers.h"
#include "Bomb.h"
#include "Block.h"
#include "Map.h"
#include "Service.h"
#include "Textures.h"

void Player::update()
{
	if (state != DEAD)
	{
		playerController();
		movePlayer();
	}
	bombs = checkBombs();
	bombsDropped = bombs.size();
}

std::vector<sp<Bomb>> Player::checkBombs()
{
	std::vector<sp<Bomb>> newBombs = {};

	for (const auto& bomb : bombs)
	{
		if (!bomb->isExploded)
		{
			newBombs.push_back(bomb);
		}
	}
	return newBombs;
}

/*
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
*/

SDL_Texture* Player::loadTexture()
{
	/*
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
	*/
	std::string name;

	switch (state) {
	case DOWN:
		name = "playerMoveDown";
		break;
	case IDLE_DOWN:
		name = "playerMoveDown";
		break;
	case UP:
		name = "playerMoveUp";
		break;
	case IDLE_UP:
		name = "playerMoveUp";
		break;
	case RIGHT:
		name = "playerMoveRight";
		break;
	case IDLE_RIGHT:
		name = "playerMoveRight";
		break;
	case LEFT:
		name = "playerMoveLeft";
		break;
	case IDLE_LEFT:
		name = "playerMoveLeft";
		break;
	case DEAD:
		name = "playerDeath";
		break;
	default:
		break;
	}
	textureName = name;
	return Service<Textures>::Get()->findTexture(textureName);
}

void Player::handleEvent(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			dropBomb();
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
		oldState = state;
		state = UP;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		oldState = state;
		state = DOWN;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		oldState = state;
		state = LEFT;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		oldState = state;
		state = RIGHT;
	}
	else {
		if (state == UP)
		{
			oldState = state;
			state = IDLE_UP;
		}
		if (state == DOWN)
		{
			oldState = state;
			state = IDLE_DOWN;
		}
		if (state == LEFT)
		{
			oldState = state;
			state = IDLE_LEFT;
		}
		if (state == RIGHT)
		{
			oldState = state;
			state = IDLE_RIGHT;
		}
		moving = false;
	}
}

void Player::movePlayer() {
	const int oldX = posX;
	const int oldY = posY;
	auto map = Service<Map>::Get();
	bool colliding = false;

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

	for (const auto& player : map->m_playerList)
	{
		for (const auto& bomb : player->bombs)
		{
			if (Helpers::checkCollision(collider, bomb->collider))
			{
				if (bomb->firstCollision)
				{
					break;
				}
				else
				{
					colliding = true;
				}
				break;
			}
			else
			{
				bomb->firstCollision = false;
			}
		}
	}
	if (!colliding)
	{
		for (const auto& block : map->tileSet)
		{
			if (block->blockType != GRASS && Helpers::checkCollision(collider, block->collider))
			{
				colliding = true;
				break;
			}
		}
	}

	if (colliding)
	{
		posX = oldX;
		windowRect.x = posX;
		collider.x = posX + PLAYER_WIDTH / 3.f;

		posY = oldY;
		windowRect.y = posY;
		collider.y = posY + PLAYER_HEIGHT / 2.f;
	}
}

void Player::renderBombs()
{
	for (const auto& bomb : bombs)
	{
		bomb->render(m_renderer);
	}
}

void Player::render() {

	renderBombs();
	animate();

	// Debug
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(m_renderer, &collider);
}

void Player::die()
{
	state = DEAD;
	timeDied = SDL_GetTicks();
	collider.h = 0;
	collider.w = 0;
	frame = 0;
}

void Player::animate()
{
	int totalFrames = 8;

	switch (state) {
	case DEAD:
		totalFrames = 5;
		break;
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

	if (oldState != state)
	{
		texture = loadTexture();
		oldState = state;
	}

	if (state == DEAD)
	{
		const Uint32 currentTime = SDL_GetTicks() - timeDied;
		const Uint32 timeSpent = currentTime - oldTime;
		if (timeSpent > delayPerFrame)
		{
			oldTime = timeSpent;
			frame++;
		}
		if (frame > totalFrames)
		{
			return;
		}
	}
	else if (moving) {
		frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
	}

	textureRect.y = frame * textureRect.h;

	SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;

	SDL_RenderCopy(m_renderer, texture, &textureRect, &windowRect);
}

void Player::dropBomb() {
	auto map = Service<Map>::Get();
	if (maxBombs > bombsDropped)
	{
		const std::pair<int, int> currentBlockIndex = Helpers::getCurrentBlock(posX, posY);
		std::pair<int, int> blockCenter = Helpers::getBlockCenter(currentBlockIndex.first, currentBlockIndex.second);
		std::pair <int, int> testIndex = Helpers::getCurrentBlock(blockCenter.first, blockCenter.second);
		const auto bomb = makesp<Bomb>(flamePower, blockCenter.first, blockCenter.second, map);
		bomb->load_textures(m_renderer, "bomb");
		bombs.emplace_back(bomb);
	}
}

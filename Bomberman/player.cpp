#include "Player.h"
#include <SDL_image.h>
#include <memory>
#include "Helpers.h"
#include "Bomb.h"
#include "Block.h"
#include "Map.h"
#include "Service.h"
#include "Textures.h"
#include "Musicplayer.h"
#include <iostream>

void Player::update()
{
	if (m_state != DEAD)
	{
		playerController();
		movePlayer();
	}
	else
	{
		if (SDL_GetTicks() - m_time_died > 2000)
		{
			m_is_alive = false;
		}
	}
	m_bombs = checkBombs();
	m_bombs_dropped = m_bombs.size();
}

std::vector<sp<Bomb>> Player::checkBombs()
{
	std::vector<sp<Bomb>> newBombs = {};

	for (const auto& bomb : m_bombs)
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

	switch (m_state) {
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
	m_texture_name = name;
	return Service<Textures>::Get()->findTexture(m_texture_name);
}

void Player::handleEvent(SDL_Event& event) {
	if (m_state != DEAD)
	{
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
}


void Player::playerController()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		m_old_state = m_state;
		m_state = UP;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		m_old_state = m_state;
		m_state = DOWN;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		m_old_state = m_state;
		m_state = LEFT;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		m_old_state = m_state;
		m_state = RIGHT;
	}
	else {
		if (m_state == UP)
		{
			m_old_state = m_state;
			m_state = IDLE_UP;
		}
		if (m_state == DOWN)
		{
			m_old_state = m_state;
			m_state = IDLE_DOWN;
		}
		if (m_state == LEFT)
		{
			m_old_state = m_state;
			m_state = IDLE_LEFT;
		}
		if (m_state == RIGHT)
		{
			m_old_state = m_state;
			m_state = IDLE_RIGHT;
		}
		m_moving = false;
	}
}

void Player::movePlayer() {
	const int oldX = m_pos_x;
	const int oldY = m_pos_y;
	auto map = Service<Map>::Get();
	bool colliding = false;

	switch (m_state) {
	case UP:
		m_pos_y -= m_speed;
		m_moving = true;
		break;
	case IDLE_UP:
		m_moving = false;
		break;
	case DOWN:
		m_pos_y += m_speed;
		m_moving = true;
		break;
	case IDLE_DOWN:
		m_moving = false;
		break;
	case LEFT:
		m_pos_x -= m_speed;
		m_moving = true;
		break;
	case IDLE_LEFT:
		m_moving = false;
		break;
	case RIGHT:
		m_pos_x += m_speed;
		m_moving = true;
		break;
	case IDLE_RIGHT:
		m_moving = false;
		break;
	default:
		break;
	}
	m_window_rect.x = m_pos_x;
	m_collider.x = m_pos_x + Config::PLAYER_WIDTH / 3.f;
	m_window_rect.y = m_pos_y;
	m_collider.y = m_pos_y + Config::PLAYER_HEIGHT / 2.f;

	for (const auto& enemy : map->m_enemyList)
	{
		if (Helpers::CheckCollision(m_collider, enemy->m_collider))
		{
			if (enemy->m_is_alive)
			{
				die();
				return;
			}
		}
	}

	for (const auto& player : map->m_playerList)
	{
		for (const auto& bomb : player->m_bombs)
		{
			if (Helpers::CheckCollision(m_collider, bomb->collider))
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
		for (const auto& blocksY : map->tileSet)
		{
			for (const auto& block : blocksY)
				if (block->m_block_type != Config::GRASS && Helpers::CheckCollision(m_collider, block->m_collider))
				{
					colliding = true;
					break;
				}
		}
	}

	if (colliding)
	{
		m_pos_x = oldX;
		m_window_rect.x = m_pos_x;
		m_collider.x = m_pos_x + Config::PLAYER_WIDTH / 3.f;

		m_pos_y = oldY;
		m_window_rect.y = m_pos_y;
		m_collider.y = m_pos_y + Config::PLAYER_HEIGHT / 2.f;
	}
}

void Player::renderBombs()
{
	for (const auto& bomb : m_bombs)
	{
		bomb->render(m_renderer);
	}
}

void Player::render() {

	renderBombs();
	animate();

	// Debug
	//SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
	//SDL_RenderDrawRect(m_renderer, &collider);
}

void Player::die()
{
	if (m_state != DEAD)
	{
		m_time_died = SDL_GetTicks();
		m_collider.h = 0;
		m_collider.w = 0;
		m_frame = 0;
		m_state = DEAD;
		MusicPlayer::PlaySoundFromPath("sounds/player_death.wav");
	}
}

void Player::animate()
{
	int totalFrames = 8;

	switch (m_state) {
	case DEAD:
		totalFrames = 5;
		break;
	case UP:
		totalFrames = 7;
		m_moving = true;
		break;
	case IDLE_UP:
		totalFrames = 7;
		m_moving = false;
		break;
	case DOWN:
		totalFrames = 8;
		m_moving = true;
		break;
	case IDLE_DOWN:
		totalFrames = 8;
		m_moving = false;
		break;
	case LEFT:
		totalFrames = 8;
		m_moving = true;
		break;
	case IDLE_LEFT:
		totalFrames = 8;
		m_moving = false;
		break;
	case RIGHT:
		totalFrames = 9;
		m_moving = true;
		break;
	case IDLE_RIGHT:
		totalFrames = 9;
		m_moving = false;
		break;
	default:
		break;
	}

	if (m_old_state != m_state)
	{
		m_texture = loadTexture();
		m_old_state = m_state;
	}

	if (m_state == DEAD)
	{
		const Uint32 currentTime = SDL_GetTicks() - m_time_died;
		const Uint32 timeSpent = currentTime - m_old_time;
		if (timeSpent > m_delay_per_frame)
		{
			m_old_time = timeSpent;
			m_frame++;
		}
		if (m_frame > totalFrames)
		{
			return;
		}
	}
	else if (m_moving) {
		m_frame = (SDL_GetTicks() / m_delay_per_frame) % totalFrames;
	}

	m_texture_rect.y = m_frame * m_texture_rect.h;

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);

	m_texture_rect.h /= totalFrames;

	SDL_RenderCopy(m_renderer, m_texture, &m_texture_rect, &m_window_rect);
}

void Player::dropBomb() {
	auto map = Service<Map>::Get();
	if (m_max_bombs > m_bombs_dropped)
	{
		const std::pair<int, int> currentBlockIndex = Helpers::GetCurrentBlock(m_pos_x, m_pos_y);
		std::pair<int, int> blockCenter = Helpers::GetBlockCenter(currentBlockIndex.first, currentBlockIndex.second);
		const auto bomb = makesp<Bomb>(m_flame_power, blockCenter.first, blockCenter.second, map);

		std::cout << "Spawning bomb to x: " << currentBlockIndex.first << " . y: " << currentBlockIndex.second << std::endl;
		bomb->load_textures(m_renderer, "bomb");
		m_bombs.emplace_back(bomb);
	}
}

#include "Enemy.h"
#include "Map.h"
#include "Service.h"
#include "Textures.h"
#include "Hud.h"
#include "Pathfinding.h"
#include "State.h"

Enemy::Enemy(const EntityType enemy_type, SDL_Renderer* renderer, const int index_x, const int index_y) :
	m_type(enemy_type), m_renderer(renderer)
{
	const auto blockCenter = Helpers::GetBlockCenter(index_x, index_y);
	m_pos_x = blockCenter.first;
	m_pos_y = blockCenter.second;
	if (m_type == EASY_ENEMY)
	{
		m_speed = 2;
		m_decision_delay = 5000;
		m_sprite = "easyEnemy";
	}
	else if (m_type == HARD_ENEMY)
	{
		m_speed = 3;
		m_decision_delay = 10;
		m_sprite = "hardEnemy";
	}
	m_state = DOWN;
	m_windowRect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	m_collider = { 0, 0, Config::BLOCK_WIDTH - PADDING_X, Config::BLOCK_HEIGHT - PADDING_Y };
}

void Enemy::update()
{
	if (m_is_alive)
	{
		loadTexture(m_sprite);

		// Add delay to decisions to change direction and stop A* from overshooting the target block
		if (SDL_GetTicks() - m_decision_time > m_decision_delay)
		{
			decide();
		}

		// A* pathfinding
		if (m_type == HARD_ENEMY)
		{
			smartMove();
		}

		// Random movement
		if (m_type == EASY_ENEMY)
		{
			move();
		}
	}
}

void Enemy::render()
{
	if (!m_is_alive && SDL_GetTicks() - m_time_died > m_death_delay) {
		return;
	}

	const int totalFrames = 6;
	const int animatedFrames = 4;
	const int delayPerFrame = 200;

	m_collider.x = m_pos_x;
	m_collider.y = m_pos_y;

	if (!m_is_alive)
	{
		m_frame = 5;
	}
	else
	{
		m_frame = (SDL_GetTicks() / delayPerFrame) % animatedFrames;
	}

	m_textureRect.y = m_frame * m_textureRect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textureRect.w, &m_textureRect.h);

	m_textureRect.h /= totalFrames;

	SDL_RenderCopy(m_renderer, m_texture, &m_textureRect, &m_windowRect);


	// Debug
	const auto state = Service<State>::Get();
	if (state->m_debug)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(m_renderer, &m_collider);

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
		SDL_RenderDrawRect(m_renderer, &m_windowRect);

		for (const auto& block : m_path)
		{
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
			SDL_RenderDrawRect(m_renderer, &block->m_collider);
		}
	}
}

void Enemy::loadTexture(std::string sprite)
{
	if (!m_texture_loaded)
	{
		auto textures = Service<Textures>::Get();
		m_texture = textures->findTexture(sprite);
		m_texture_loaded = true;
	}
}

void Enemy::decide()
{
	if (m_type == HARD_ENEMY)
	{
		auto map = Service<Map>::Get();
		const auto player = map->m_playerList.front();
		target_block = map->findBlockByCoordinates(player->getPositionX(), player->getPositionY());
		current_block = map->findBlockByCoordinates(m_pos_x, m_pos_y);

		// Only get new path if target block has changed
		if (m_old_target_x != target_block->m_index_x || m_old_target_y != target_block->m_index_y)
		{
			m_path = Pathfinding::calculatePath(target_block, current_block);
		}

		m_decision_time = SDL_GetTicks();
		m_old_target_x = target_block->m_index_x;
		m_old_target_y = target_block->m_index_y;
	}
	else if (m_type == EASY_ENEMY)
	{
		const int random = rand() % 12;

		switch (m_state)
		{
		case UP:
			if (random < 4)
			{
				m_state = LEFT;
			}
			else if (random > 3 && random < 9)
			{
				m_state = RIGHT;
			}
			else
			{
				m_state = DOWN;
			}
			break;
		case DOWN:
			if (random < 4)
			{
				m_state = LEFT;
			}
			else if (random > 3 && random < 9)
			{
				m_state = RIGHT;
			}
			else
			{
				m_state = UP;
			}
			break;
		case LEFT:
			if (random < 4)
			{
				m_state = UP;
			}
			else if (random > 3 && random < 9)
			{
				m_state = DOWN;
			}
			else
			{
				m_state = RIGHT;
			}
			break;
		case RIGHT:
			if (random < 4)
			{
				m_state = UP;
			}
			else if (random > 3 && random < 9)
			{
				m_state = DOWN;
			}
			else
			{
				m_state = LEFT;
			}
			break;
		default:
			break;
		}
		m_decision_time = SDL_GetTicks();
	}
}

void Enemy::move()
{
	auto map = Service<Map>::Get();
	const int oldX = m_pos_x;
	const int oldY = m_pos_y;
	bool colliding = false;

	switch (m_state) {
	case UP:
		m_pos_y -= m_speed;
		break;
	case DOWN:
		m_pos_y += m_speed;
		break;
	case LEFT:
		m_pos_x -= m_speed;
		break;
	case RIGHT:
		m_pos_x += m_speed;
		break;
	default:
		break;
	}
	m_windowRect.x = m_pos_x;
	m_collider.x = m_pos_x + PADDING_X;
	m_windowRect.y = m_pos_y;
	m_collider.y = m_pos_y + PADDING_Y;

	for (const auto& player : map->m_playerList)
	{
		for (const auto& bomb : player->m_bombs)
		{
			if (Helpers::CheckCollision(m_collider, bomb->collider))
			{
				colliding = true;
				break;
			}
		}
	}
	if (!colliding)
	{
		for (int x = 0; x < MAX_BLOCKS_X; x++) {
			for (int y = 0; y < MAX_BLOCKS_Y; y++) {
				{
					if (map->tileSet[x][y]->m_block_type != GRASS && Helpers::CheckCollision(m_collider, map->tileSet[x][y]->m_collider))
					{
						colliding = true;
						break;
					}
				}
			}
		}
	}
	if (colliding)
	{
		m_pos_x = oldX;
		m_windowRect.x = m_pos_x;
		m_collider.x = m_pos_x + PADDING_X;;

		m_pos_y = oldY;
		m_windowRect.y = m_pos_y;
		m_collider.y = m_pos_y + PADDING_Y;
		decide();
	}

}
void Enemy::smartMove()
{
	auto map = Service<Map>::Get();
	const int oldX = m_pos_x;
	const int oldY = m_pos_y;
	bool colliding = false;

	if (!m_path.empty())
	{
		m_next_block = m_path.front();
		const auto nextBlockCoordinates = Helpers::GetBlockCenter(m_next_block->m_index_x, m_next_block->m_index_y);

		m_speed_x = 0;
		m_speed_y = 0;

		const int delta_x = abs(m_next_block->m_index_x - current_block->m_index_x);
		const int delta_y = abs(m_next_block->m_index_y - current_block->m_index_y);

		if (delta_x >= delta_y) {

			if (m_pos_x > nextBlockCoordinates.first)
			{
				m_speed_x -= m_speed;
			}
			else
			{
				m_speed_x += m_speed;
			}
		}
		else
		{
			if (m_pos_y > nextBlockCoordinates.second)
			{
				m_speed_y -= m_speed;
			}
			else
			{
				m_speed_y += m_speed;
			}
		}
		m_pos_y += m_speed_y;
		m_pos_x += m_speed_x;
	}

	m_windowRect.x = m_pos_x;
	m_collider.x = m_pos_x + PADDING_X;
	m_windowRect.y = m_pos_y;
	m_collider.y = m_pos_y + PADDING_Y;

	for (const auto& player : map->m_playerList)
	{
		for (const auto& bomb : player->m_bombs)
		{
			if (Helpers::CheckCollision(m_collider, bomb->collider))
			{
				colliding = true;
				break;
			}
		}
	}
	if (!colliding)
	{
		for (auto& x : map->tileSet)
		{
			for (const auto& y : x)
			{
				if (y->m_block_type != GRASS && Helpers::CheckCollision(m_collider, y->m_collider))
				{
					colliding = true;
					break;
				}
			}
		}
	}

	if (colliding)
	{
		m_pos_x = oldX;
		m_windowRect.x = m_pos_x;
		m_collider.x = m_pos_x + PADDING_X;;

		m_pos_y = oldY;
		m_windowRect.y = m_pos_y;
		m_collider.y = m_pos_y + PADDING_Y;
	}
}

void Enemy::die()
{
	m_time_died = SDL_GetTicks();
	m_is_alive = false;
	Service<State>::Get()->incrementScore(m_score);
}

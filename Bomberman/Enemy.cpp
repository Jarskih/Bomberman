#include "Enemy.h"
#include "Map.h"
#include "Service.h"
#include "Textures.h"
#include "Hud.h"
#include "Pathfinding.h"

void Enemy::update()
{
	if (SDL_GetTicks() - m_decision_time > m_decision_delay)
	{
		decide();
	}
	if (m_is_alive)
	{
		loadTexture(m_sprite);
		if (m_enemy_type == HARD)
		{
			smartMove();
		}
		else if (m_enemy_type == EASY)
		{
			randomMove();
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

	// Debug

	// SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	// SDL_RenderDrawRect(m_renderer, &collider);

	// SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	// SDL_RenderDrawRect(m_renderer, &windowRect);

	for (const auto& block : m_path)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(m_renderer, &block->m_collider);
	}

	if (!m_is_alive)
	{
		m_frame = 5;
	}
	else
	{
		m_frame = (SDL_GetTicks() / delayPerFrame) % animatedFrames;
	}

	m_texture_rect.y = m_frame * m_texture_rect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);

	m_texture_rect.h /= totalFrames;

	SDL_RenderCopy(m_renderer, m_texture, &m_texture_rect, &m_window_rect);
}

void Enemy::loadTexture(const std::string sprite)
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
	m_decision_time = SDL_GetTicks();

	if (m_enemy_type == HARD)
	{
		auto map = Service<Map>::Get();
		const auto player = map->m_playerList.front();
		target_block = map->findBlockByCoordinates(player->getPositionX(), player->getPositionY());
		current_block = map->findBlockByCoordinates(m_pos_x, m_pos_y);
		m_path = Pathfinding::calculatePath(target_block, current_block);
	}
	else if (m_enemy_type == EASY)
	{
		int random = rand() % 10;

		switch (m_state)
		{
		case UP:
			if (random < 4)
			{
				m_state = LEFT;
			}
			else if (random > 3 && random < 8)
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
			else if (random > 3 && random < 8)
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
			else if (random > 3 && random < 8)
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
			else if (random > 3 && random < 8)
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
	}
}

void Enemy::randomMove()
{
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
}

void Enemy::smartMove()
{
	auto map = Service<Map>::Get();

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
				m_speed_x = -m_speed;
			}
			else
			{
				m_speed_x = m_speed;
			}
		}
		else
		{
			if (m_pos_y > nextBlockCoordinates.second)
			{
				m_speed_y = -m_speed;
			}
			else
			{
				m_speed_y = m_speed;
			}
		}
		m_pos_y += m_speed_y;
		m_pos_x += m_speed_x;
	}
}

void Enemy::checkCollisions()
{
	const int oldX = m_pos_x;
	const int oldY = m_pos_y;
	bool colliding = false;

	m_window_rect.x = m_pos_x;
	m_collider.x = m_pos_x + PADDING_X;
	m_window_rect.y = m_pos_y;
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

		if (colliding)
		{
			m_pos_x = oldX;
			m_window_rect.x = m_pos_x;
			m_collider.x = m_pos_x + PADDING_X;;

			m_pos_y = oldY;
			m_window_rect.y = m_pos_y;
			m_collider.y = m_pos_y + PADDING_Y;
			decide();
		}
	}
}

void Enemy::die()
{
	m_time_died = SDL_GetTicks();
	m_is_alive = false;
	Service<State>::Get()->incrementScore(m_score);
}

#include "Enemy.h"
#include "Map.h"
#include "Service.h"
#include "Textures.h"
#include "Hud.h"
#include "Pathfinding.h"

void Enemy::update()
{
	if (SDL_GetTicks() - decisionTime > decisionDelay)
	{
		decide();
	}
	if (isAlive)
	{
		loadTexture(m_sprite);
		move();
	}
}

void Enemy::render()
{
	if (!isAlive && SDL_GetTicks() - timeDied > deathDelay) {
		return;
	}

	const int totalFrames = 6;
	const int animatedFrames = 4;
	const int delayPerFrame = 200;

	collider.x = m_pos_x;
	collider.y = m_pos_y;

	// Debug

	// SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	// SDL_RenderDrawRect(m_renderer, &collider);

	// SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	// SDL_RenderDrawRect(m_renderer, &windowRect);

	for (auto block : path)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(m_renderer, &block->collider);
	}

	if (!isAlive)
	{
		frame = 5;
	}
	else
	{
		frame = (SDL_GetTicks() / delayPerFrame) % animatedFrames;
	}

	textureRect.y = frame * textureRect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;

	SDL_RenderCopy(m_renderer, m_texture, &textureRect, &windowRect);
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
	decisionTime = SDL_GetTicks();

	auto map = Service<Map>::Get();
	auto player = map->m_playerList.front();
	targetBlock = map->findBlockByCoordinates(player->getPositionX(), player->getPositionY());
	currentBlock = map->findBlockByCoordinates(m_pos_x, m_pos_y);
	path = Pathfinding::calculatePath(targetBlock, currentBlock);

	int random = rand() % 10;

	/*
	switch (state)
	{
	case UP:
		if (random < 4)
		{
			state = LEFT;
		}
		else if (random > 3 && random < 8)
		{
			state = RIGHT;
		}
		else
		{
			state = DOWN;
		}
		break;
	case DOWN:
		if (random < 4)
		{
			state = LEFT;
		}
		else if (random > 3 && random < 8)
		{
			state = RIGHT;
		}
		else
		{
			state = UP;
		}
		break;
	case LEFT:
		if (random < 4)
		{
			state = UP;
		}
		else if (random > 3 && random < 8)
		{
			state = DOWN;
		}
		else
		{
			state = RIGHT;
		}
		break;
	case RIGHT:
		if (random < 4)
		{
			state = UP;
		}
		else if (random > 3 && random < 8)
		{
			state = DOWN;
		}
		else
		{
			state = LEFT;
		}
		break;
	default:
		break;
	}
	*/
}

void Enemy::move()
{
	auto map = Service<Map>::Get();
	const int oldX = m_pos_x;
	const int oldY = m_pos_y;
	bool colliding = false;

	if (!path.empty())
	{
		nextBlock = path.front();


		int delta_x = abs(nextBlock->index_x - currentBlock->index_x);
		int delta_y = abs(nextBlock->index_y - currentBlock->index_y);

		if (delta_x >= delta_y)
		{
			if (nextBlock->index_x < currentBlock->index_x)
			{
				speed_x = -speed;
			}
			else
			{
				speed_x = speed;
			}

		}
		else
		{
			if (nextBlock->index_y < currentBlock->index_y)
			{
				speed_y = -speed;
			}
			else
			{
				speed_y = speed;
			}
		}

		m_pos_y += speed_y;
		m_pos_x += speed_x;
	}


	/*
	switch (state) {
	case UP:
		m_pos_y -= speed;
		break;
	case DOWN:
		m_pos_y += speed;
		break;
	case LEFT:
		m_pos_x -= speed;
		break;
	case RIGHT:
		m_pos_x += speed;
		break;
	default:
		break;
	}
	*/
	windowRect.x = m_pos_x;
	collider.x = m_pos_x + PADDING_X;
	windowRect.y = m_pos_y;
	collider.y = m_pos_y + PADDING_Y;

	for (const auto& player : map->m_playerList)
	{
		for (const auto& bomb : player->bombs)
		{
			if (Helpers::checkCollision(collider, bomb->collider))
			{
				// auto collisionList = bomb->enemyFirstCollision;
				// auto it = std::find(collisionList.begin(), collisionList.end(), this);
				if (true)
				{
					colliding = true;
					break;
				}
				else
				{
					// TODO add to list
					//collisionList->push_back(this);
				}

			}
		}
	}
	if (!colliding)
	{
		for (int x = 0; x < MAX_BLOCKS_X; x++) {
			for (int y = 0; y < MAX_BLOCKS_Y; y++) {
				{
					if (map->tileSet[x][y]->blockType != GRASS && Helpers::checkCollision(collider, map->tileSet[x][y]->collider))
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
			windowRect.x = m_pos_x;
			collider.x = m_pos_x + PADDING_X;;

			m_pos_y = oldY;
			windowRect.y = m_pos_y;
			collider.y = m_pos_y + PADDING_Y;
			decide();
		}
	}
}

void Enemy::die()
{
	timeDied = SDL_GetTicks();
	isAlive = false;
	Service<State>::Get()->incrementScore(m_score);
}

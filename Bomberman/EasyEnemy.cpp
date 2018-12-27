#include "EasyEnemy.h"
#include "Map.h"
#include "Service.h"
#include "Textures.h"

void EasyEnemy::update(const sp<Map> &map)
{
	loadTexture(m_sprite);
	if (SDL_GetTicks() - decisionTime > decisionDelay)
	{
		decide();
	}
	move(map->tileSet);
}

void EasyEnemy::render(const sp<Map> &map)
{

	collider.x = m_pos_x;
	collider.y = m_pos_y;
	// Debug

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(m_renderer, &collider);

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(m_renderer, &windowRect);

	const int totalFrames = 6;
	const int animatedFrames = 4;
	const int delayPerFrame = 200;
	int frame = (SDL_GetTicks() / delayPerFrame) % animatedFrames;

	textureRect.y = frame * textureRect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;

	SDL_RenderCopy(m_renderer, m_texture, &textureRect, &windowRect);
}

void EasyEnemy::loadTexture(std::string sprite)
{
	if (!m_texture_loaded)
	{
		auto textures = Service<Textures>::Get();
		m_texture = textures->findTexture(sprite);
		m_texture_loaded = true;
	}
}

void EasyEnemy::decide()
{
	decisionTime = SDL_GetTicks();
	int random = rand() % 10;

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
}

void EasyEnemy::move(std::vector<sp<Block>> blocks)
{
	const int oldX = m_pos_x;
	const int oldY = m_pos_y;

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
	windowRect.x = m_pos_x;
	collider.x = m_pos_x + PADDING_X;
	windowRect.y = m_pos_y;
	collider.y = m_pos_y + PADDING_Y;

	for (const auto& block : blocks)
	{
		if (block->blockType != GRASS && checkCollision(collider, block->collider))
		{
			m_pos_x = oldX;
			windowRect.x = m_pos_x;
			collider.x = m_pos_x + PADDING_X;;

			m_pos_y = oldY;
			windowRect.y = m_pos_y;
			collider.y = m_pos_y + PADDING_Y;
			decide();
			break;
		}
	}
}

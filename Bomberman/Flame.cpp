#include "Flame.h"
#include <SDL_image.h>
#include "Service.h"
#include "Textures.h"
#include "Map.h"

void Flame::loadTextures(std::string sprite)
{
	if (!m_texture_loaded)
	{
		auto textures = Service<Textures>::Get();
		m_texture = textures->findTexture(sprite);
		m_texture_loaded = true;
	}
}

void Flame::setTexture(SDL_Texture* texture)
{
	m_texture = texture;
}

void Flame::render(int frame)
{

	int totalFrames = 4;

	if (frame < totalFrames)
	{
		textureRect.y = frame * textureRect.h;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

		textureRect.h /= totalFrames;

		SDL_RenderCopy(m_renderer, m_texture, &textureRect, &windowRect);
	}

	// SDL_RenderDrawRect(m_renderer, &collider);
}

void Flame::colliderResize(int x, int y, int width, int height)
{
	collider.x += x;
	collider.y += y;
	collider.w = width;
	collider.h = height;
}

void Flame::checkCollision() const
{
	auto map = Service<Map>::Get();
	for (const auto& player : map->m_playerList)
	{
		if (Helpers::CheckCollision(collider, player->getCollider()))
		{
			player->die();
		}

		for (const auto& bomb : player->m_bombs)
		{
			if (Helpers::CheckCollision(collider, bomb->collider))
			{
				bomb->hitFlame = true;
			}
		}
		for (const auto& enemy : map->m_enemyList)
		{
			if (Helpers::CheckCollision(collider, enemy->m_collider))
			{
				if (enemy->m_is_alive) {
					enemy->die();
				}
			}
		}
	}
}

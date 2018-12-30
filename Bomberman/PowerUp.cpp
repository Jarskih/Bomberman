#include "PowerUp.h"
#include "Map.h"

void PowerUp::render()
{
	if (isPickedUp) {
		return;
	}
	const int delayPerFrame = 200;

	// Debug

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(m_renderer, &collider);

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
	SDL_RenderDrawRect(m_renderer, &windowRect);

	frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;

	textureRect.y = frame * textureRect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;
	textureRect.w /= 5;
	textureRect.x = m_type * textureRect.w;

	SDL_RenderCopy(m_renderer, m_texture, &textureRect, &windowRect);
}

void PowerUp::checkCollision(const std::vector<sp<Player>>& m_playerList)
{
	if (!isPickedUp) {
		for (const auto& player : m_playerList)
		{
			if (Helpers::checkCollision(collider, player->collider))
			{
				isPickedUp = true;
				if (m_type == 0)
				{
					player->flamePower++;
				}
				else if (m_type == 1)
				{
					player->maxBombs++;
				}
			}
		}
	}
}

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

	auto map = Service<Map>::Get();
	if (m_type == EXIT && !map->levelCleared)
	{
		frame = 0;
	}
	else
	{
		frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
	}

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
				auto state = Service<State>::Get();
				state->incrementScore(m_score);
				isPickedUp = true;
				auto map = Service<Map>::Get();
				switch (m_type)
				{
				case FLAME:
					player->flamePower++;
					break;
				case BOMB:
					player->maxBombs++;
					break;
				case SPEED:
					player->speed++;
					break;
				case LIFE:
					state->incrementLives();
					break;
				case EXIT:
					if (map->levelCleared)
					{
						map->win();
					}
					else
					{
						isPickedUp = false;
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

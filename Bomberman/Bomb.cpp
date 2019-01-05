#include "Bomb.h"
#include <iostream>
#include <SDL_image.h>
#include "Map.h"
#include "Textures.h"
#include "Service.h"
#include "Musicplayer.h"

void Bomb::render(SDL_Renderer* renderer)
{
	const Uint32 currentTime = SDL_GetTicks() - timeDropped;
	const Uint32 timeSpent = currentTime - oldTime;

	if (timeSpent > bombTimer || hitFlame)
	{
		if (!explosionSound)
		{
			MusicPlayer::PlaySound("sounds/bomb.wav");
			explosionSound = true;
		}
		explode(renderer);
	}
	else
	{
		const int totalFrames = 3;
		const int delayPerFrame = 200;
		const int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
		textureRect.y = frame * textureRect.h;
		SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

		textureRect.h /= totalFrames;

		SDL_RenderCopy(renderer, texture, &textureRect, &windowRect);

		oldTime = timeSpent;
	}

	//Debug

	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect(renderer, &collider);
}

void Bomb::load_textures(SDL_Renderer* renderer, const std::string &sprite)
{
	std::string spritePath = spritePaths[sprite];
	const char* c = spritePath.c_str();

	SDL_Surface* surface = IMG_Load(c);
	if (!surface) {
		std::cout << "Cant load bomb m_texture" << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Bomb::explode(SDL_Renderer* renderer)
{
	SDL_Texture* m_texture = Service<Textures>::Get()->findTexture("explosionCenter");
	const Uint32 delayPerFrame = 200;

	const int totalFrames = 5;

	if (timeExploded == 0)
	{
		timeExploded = SDL_GetTicks();
	}

	if (SDL_GetTicks() - timeExploded >= delayPerFrame * explosion_frame)
	{
		explosion_frame++;
	}

	renderFlames(renderer, explosion_frame);

	textureRect.y = explosion_frame * textureRect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;

	SDL_RenderCopy(renderer, m_texture, &textureRect, &windowRect);

	if (explosion_frame >= totalFrames)
	{
		isExploded = true;
	}
}

void Bomb::renderFlames(SDL_Renderer* renderer, int frames)
{
	if (flames.empty())
	{
		// Up
		for (int range = 1; range <= m_flamePower; range++)
		{
			int y = index_y - range;
			if (canSpawnFlame(m_map, index_x, y))
			{
				auto flame = makesp<Flame>(index_x, y, range, m_flamePower, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameY");
				}
				else
				{
					flame->loadTextures("lastUp");
				}
				flame->colliderResize(BLOCK_WIDTH / 4, 0, BLOCK_WIDTH / 2, BLOCK_HEIGHT);
				flames.push_back(flame);
				std::cout << "Spawning flame up to x: " << index_x << ". And y: " << y << std::endl;
			}
			else
			{
				break;
			}
		}
		// Down
		for (int range = 1; range <= m_flamePower; range++)
		{
			int y = index_y + range;
			if (canSpawnFlame(m_map, index_x, y))
			{
				auto flame = makesp<Flame>(index_x, y, range, m_flamePower, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameY");
				}
				else
				{
					flame->loadTextures("lastDown");
				}
				flame->colliderResize(BLOCK_WIDTH / 4, 0, BLOCK_WIDTH / 2, BLOCK_HEIGHT);
				flames.push_back(flame);
				std::cout << "Spawning flame down to x: " << index_x << ". And y: " << y << std::endl;
			}
			else
			{
				break;
			}
		}
		// Left
		for (int range = 1; range <= m_flamePower; range++)
		{
			int x = index_x - range;
			if (canSpawnFlame(m_map, x, index_y))
			{
				auto flame = makesp<Flame>(x, index_y, range, m_flamePower, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameX");
				}
				else
				{
					flame->loadTextures("lastLeft");
				}
				flame->colliderResize(0, BLOCK_HEIGHT / 4, BLOCK_WIDTH, BLOCK_HEIGHT / 2);
				flames.push_back(flame);
				std::cout << "Spawning flame left to x: " << x << ". And y: " << index_y << std::endl;
			}
			else
			{
				break;
			}
		}
		// Right
		for (int range = 1; range <= m_flamePower; range++)
		{
			int x = index_x + range;
			if (canSpawnFlame(m_map, x, index_y))
			{
				auto flame = makesp<Flame>(x, index_y, range, m_flamePower, renderer);
				if (range < m_flamePower)
				{
					flame->loadTextures("flameX");
				}
				else
				{
					flame->loadTextures("lastRight");
				}
				flame->colliderResize(0, BLOCK_HEIGHT / 4, BLOCK_WIDTH, BLOCK_HEIGHT / 2);
				flames.push_back(flame);
				std::cout << "Spawning flame right to x: " << x << ". And y: " << index_y << std::endl;
			}
			else
			{
				break;
			}
		}
	}
	for (const auto& flame : flames)
	{
		flame->checkCollision();
		flame->render(frames);
	}
}

bool Bomb::canSpawnFlame(const sp<Map> &map, const int index_x, const int index_y)
{
	bool allowed = false;
	for (const auto& block : map->tileSet)
	{
		if (block->getBlockIndex().first == index_x && block->getBlockIndex().second == index_y)
		{
			switch (block->blockType) {
			case GRASS:
				allowed = true;
				break;
			case BREAKABLE:
				block->changeBlockType(DESTROYED);
				break;
			default:
				break;
			}
		}
	}
	return allowed;
}

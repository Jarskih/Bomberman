#include "Bomb.h"
#include <iostream>
#include <SDL_image.h>
#include "Map.h"
#include "Textures.h"
#include "Service.h"

void Bomb::render(SDL_Renderer* renderer, const sp<Map> &map)
{
	const Uint32 currentTime = SDL_GetTicks() - timeDropped;
	const Uint32 timeSpent = currentTime - oldTime;

	if (timeSpent > bombTimer)
	{
		explode(renderer);
		renderFlames(renderer, map);
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
}

void Bomb::load_textures(SDL_Renderer* renderer, const std::string &sprite)
{
	std::string spritePath = spritePaths[sprite];
	const char* c = spritePath.c_str();

	SDL_Surface* surface = IMG_Load(c);
	if (!surface) {
		std::cout << "Cant load bomb texture" << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Bomb::explode(SDL_Renderer* renderer)
{
	//load_textures(renderer, "explosionCenter");
	SDL_Texture* m_texture = Service<Textures>::Get()->findTexture("explosionCenter");
	const Uint32 delayPerFrame = 200;

	const int totalFrames = 5;

	if (timeExploded == 0)
	{
		timeExploded = SDL_GetTicks();
	}

	if (SDL_GetTicks() - timeExploded >= delayPerFrame * explosionframe)
	{
		explosionframe++;
	}

	textureRect.y = explosionframe * textureRect.h;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.h /= totalFrames;

	SDL_RenderCopy(renderer, m_texture, &textureRect, &windowRect);

	if (explosionframe >= totalFrames)
	{
		isExploded = true;
	}
}

void Bomb::renderFlames(SDL_Renderer* renderer, const sp<Map> &map)
{
	if (flames.empty())
	{
		// Up
		for (int i = m_flamePower; i > 0; i--)
		{
			int y = index_y - i;
			auto flame = makesp<Flame>(index_x, y, m_flamePower, m_flamePower, renderer);
			flame->loadTextures("lastUp");
			// auto texture = Service<Textures>::Get();
			// flame->setTexture(texture->findTexture("lastUp"));
			flames.emplace_back(flame);
		}
		// Down
		for (int i = m_flamePower; i > 0; i--)
		{
			int y = index_y + i;
			auto flame = makesp<Flame>(index_x, y, m_flamePower, m_flamePower, renderer);
			auto texture = Service<Textures>::Get();
			flame->setTexture(texture->findTexture("lastDown"));
			flames.emplace_back(flame);
		}
		// Left
		for (int i = m_flamePower; i > 0; i--)
		{
			int x = index_x - i;
			auto flame = makesp<Flame>(x, index_y, m_flamePower, m_flamePower, renderer);
			auto texture = Service<Textures>::Get();
			flame->setTexture(texture->findTexture("lastLeft"));
			flames.emplace_back(flame);
		}
		// Right
		for (int i = m_flamePower; i > 0; i--)
		{
			int x = index_x + i;
			auto flame = makesp<Flame>(x, index_y, m_flamePower, m_flamePower, renderer);
			auto texture = Service<Textures>::Get();
			flame->setTexture(texture->findTexture("lastRight"));
			flames.emplace_back(flame);
		}
	}
	for (const auto& flame : flames)
	{
		flame->render(renderer);
	}
}

bool Bomb::canSpawnFlame(const sp<Map> &map, const int index_x, const int index_y)
{
	bool allowed = false;
	for (auto block : map->tileSet)
	{
		if (block->getBlockIndex().first == index_x && block->getBlockIndex().second == index_y)
		{
			if (block->blockType == GRASS)
			{
				allowed = true;
			}
		}
	}
	return allowed;
}

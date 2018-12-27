#include "Flame.h"
#include <SDL_image.h>
#include "Service.h"
#include "Textures.h"
#include <iostream>

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

	SDL_RenderDrawRect(m_renderer, &collider);
}

void Flame::colliderResize(int x, int y, int width, int height)
{
	collider.x += x;
	collider.y += y;
	collider.w = width;
	collider.h = height;
}

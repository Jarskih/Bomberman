#include "Flame.h"
#include <SDL_image.h>
#include <iostream>

void Flame::loadTextures(const std::string& sprite)
{
	if (!m_texture_loaded)
	{
		std::string spritePath = spritePaths[sprite];
		const char* c = spritePath.c_str();

		SDL_Surface* surface = IMG_Load(c);
		if (!surface) {
			std::cout << "Cant load flame texture" << std::endl;
		}
		m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);
		m_texture_loaded = true;
	}
}


void Flame::setTexture(SDL_Texture* texture)
{
	m_texture = texture;
}

void Flame::render(SDL_Renderer* renderer)
{
	const int totalFrames = 4;

	if (m_current_frame < totalFrames)
	{
		textureRect.y = m_current_frame * textureRect.h;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

		textureRect.h /= totalFrames;

		SDL_RenderCopy(renderer, m_texture, &textureRect, &windowRect);

		m_current_frame++;
		SDL_Delay(10);
	}
}

#include "Hud.h"

bool Hud::loadFromRenderedText(std::string &textureText, SDL_Color textColor)
{
	free(nullptr);

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		if (m_textTexture == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			m_width = textSurface->w;
			m_height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	return m_textTexture != nullptr;
}

bool Hud::loadFont()
{
	bool success = true;

	m_font = TTF_OpenFont("font/8bit.ttf", 24);
	if (m_font == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}

void Hud::render()
{
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_hudRect);

	auto lives = std::to_string(m_lives);
	if (!loadFromRenderedText(lives, textColor))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text texture!\n");
	}
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_livesRect);


	auto time = std::to_string(m_time);
	if (!loadFromRenderedText(time, textColor))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text texture!\n");
	}
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_timeRect);

	auto score = std::to_string(m_score);
	if (!loadFromRenderedText(score, textColor))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text texture!\n");
	}
	SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &m_scoreRect);
}

void Hud::incrementScore(int score)
{
	m_score = m_score + score;
}

#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameRules.h"
#include <string>
#include "Timer.h"
#include "Helpers.h"

class Hud
{
public:
	Hud(SDL_Renderer* renderer, SDL_Texture* hudTexture) : m_renderer(renderer), m_texture(hudTexture)
	{
		loadFont();
	};
	void render(const sp<Timer>& timer);
	void incrementScore(int score);
private:
	bool loadFromRenderedText(std::string &textureText, SDL_Color textColor);
	bool loadFont();
	int m_width = 0;
	int m_height = 0;
	SDL_Renderer* m_renderer;
	TTF_Font* m_font = nullptr;
	SDL_Color textColor = { 255, 255, 255 };
	int m_score = 0;
	int m_min = 0;
	int m_sec = 0;
	int m_lives = 0;
	SDL_Texture* m_textTexture = nullptr;
	SDL_Texture* m_texture = nullptr;
	SDL_Rect m_hudRect = { 0, 0, SCREEN_WIDTH, BLOCK_HEIGHT };
	SDL_Rect m_scoreRect = { BLOCK_WIDTH * 4, BLOCK_HEIGHT / 4, BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2 };
	SDL_Rect m_livesRect = { BLOCK_WIDTH * 9, BLOCK_HEIGHT / 4, BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2 };
	SDL_Rect m_secRect = { BLOCK_WIDTH * 7, BLOCK_HEIGHT / 4, BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2 };
	SDL_Rect m_minRect = { BLOCK_WIDTH * 6 + BLOCK_WIDTH / 2, BLOCK_HEIGHT / 4, BLOCK_WIDTH / 3, BLOCK_HEIGHT / 2 };
};

#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include "Config.h"
#include "Helpers.h"
#include <iostream>

class Flame
{
public:
	Flame() = delete;
	Flame(int x, int y, SDL_Renderer* renderer) :
		m_index_x(x),
		m_index_y(y),
		m_renderer(renderer)
	{
		m_window_rect = { Helpers::GetBlockCenter(x, y).first, Helpers::GetBlockCenter(x, y).second, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
		m_texture_rect = { 0, 0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
		m_collider = { Helpers::GetBlockCenter(x, y).first, Helpers::GetBlockCenter(x, y).second, 0, 0 };
	};
	~Flame() = default;
	void loadTextures(std::string sprite);
	void setTexture(SDL_Texture* texture);
	void render(int frame);
	void colliderResize(int x, int y, int width, int height);
	void checkCollision() const;
	int totalFrames = 4;

private:
	int m_index_x = 0;
	int m_index_y = 0;
	SDL_Renderer* m_renderer = nullptr;

	bool m_texture_loaded = false;
	SDL_Texture* m_texture = nullptr;
	SDL_Rect m_window_rect = {};
	SDL_Rect m_texture_rect = {};
	SDL_Rect m_collider = {};
};


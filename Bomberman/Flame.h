#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include "GameRules.h"
#include "Helpers.h"

class Flame
{
public:
	Flame(int x, int y, int distance, int power, SDL_Renderer* renderer) :
		m_index_x(x),
		m_index_y(y),
		m_distance_from_center(distance),
		m_bomb_power(power), m_renderer(renderer),
		m_texture(nullptr)
	{
		windowRect = { Helpers::GetBlockCenter(x, y).first, Helpers::GetBlockCenter(x, y).second, BLOCK_WIDTH, BLOCK_HEIGHT };
		textureRect = { 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT };
		collider = { Helpers::GetBlockCenter(x, y).first, Helpers::GetBlockCenter(x, y).second, 0, 0 };
	};
	~Flame() = default;
	void loadTextures(std::string sprite);
	void setTexture(SDL_Texture* texture);
	void render(int frame);
	void colliderResize(int x, int y, int width, int height);
	void checkCollision() const;

private:
	int m_index_x;
	int m_index_y;
	int m_distance_from_center;
	int m_bomb_power;
	SDL_Renderer* m_renderer;

	bool m_texture_loaded = false;
	SDL_Texture* m_texture;
	SDL_Rect windowRect;
	SDL_Rect textureRect;
	SDL_Rect collider;
	//std::map<std::string, SDL_Texture*> textures;
	//std::map<std::string, std::string> spritePaths;
};


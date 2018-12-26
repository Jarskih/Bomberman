#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include "GameRules.h"
#include "Helpers.h"

class Flame
{
public:
	Flame(int x, int y, int distance, int power, SDL_Renderer* renderer) : m_index_x_(x), m_index_y(y), m_distance_from_center(distance), m_bomb_power_(power), m_renderer(renderer)
	{
		spritePaths["flameCenter"] = "img/flame_center.png";
		spritePaths["lastRight"] = "img/flame_right_end.png";
		spritePaths["lastUp"] = "img/flame_up_end.png";
		spritePaths["lastLeft"] = "img/flame_left_end.png";
		spritePaths["lastDown"] = "img/flame_down_end.png";
		spritePaths["flameX"] = "img/flame_middle_y.png";
		spritePaths["flameY"] = "img/flame_middle_x.png";
		windowRect = { getBlockCenter(x, y).first, getBlockCenter(x, y).second, BLOCK_WIDTH, BLOCK_HEIGHT };
		textureRect = { getBlockCenter(x, y).first, getBlockCenter(x, y).second, BLOCK_WIDTH, BLOCK_HEIGHT };
	};
	~Flame() = default;
	void loadTextures(const std::string &sprite);
	void setTexture(SDL_Texture* texture);
	void render(SDL_Renderer* renderer);

private:
	int m_index_x_ = 0;
	int m_index_y = 0;
	int m_distance_from_center;
	int m_bomb_power_;
	SDL_Renderer* m_renderer;

	int m_current_frame = 0;
	bool m_texture_loaded = false;
	SDL_Texture* m_texture;
	SDL_Rect windowRect;
	SDL_Rect textureRect;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, std::string> spritePaths;
};


#include "Textures.h"
#include <SDL_image.h>
#include <iostream>


Textures::Textures(SDL_Renderer* renderer) : m_renderer(renderer)
{
	save_sprite_paths();
	create_textures();
}

SDL_Texture* Textures::findTexture(std::string name)
{
	if (textures[name] != nullptr)
	{
		return textures[name];
	}
	std::cout << "Cant find texture: " << name << std::endl;
	return nullptr;
}

void Textures::save_sprite_paths()
{
	spritePaths["flameCenter"] = "img/flame_center.png";
	spritePaths["lastRight"] = "img/flame_right_end.png";
	spritePaths["lastUp"] = "img/flame_up_end.png";
	spritePaths["lastLeft"] = "img/flame_left_end.png";
	spritePaths["lastDown"] = "img/flame_down_end.png";
	spritePaths["flameY"] = "img/flame_middle_y.png";
	spritePaths["flameX"] = "img/flame_middle_x.png";
	spritePaths["bomb"] = "img/bomb.png";
	spritePaths["explosionCenter"] = "img/flame_center.png";
}

void Textures::create_textures()
{
	for (const auto& path : spritePaths)
	{
		std::string spritePath = spritePaths[path.first];
		const char* c = spritePath.c_str();

		SDL_Surface* surface = IMG_Load(c);
		if (!surface) {
			std::cout << "Cant load texture with path: " << path.first << std::endl;
		}
		else
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
			SDL_FreeSurface(surface);
			textures[path.first] = texture;
		}
	}
}

#include "Textures.h"
#include <SDL_image.h>
#include <iostream>


Textures::Textures(SDL_Renderer* renderer) : m_renderer(renderer)
{
	save_sprite_paths();
	create_textures();
}

SDL_Texture* Textures::findTexture(const std::string &name)
{
	if (textures[name] != nullptr)
	{
		return textures[name];
	}
	else
	{
		std::cout << "Cant find m_texture: " << name << std::endl;
		return nullptr;
	}

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
	spritePaths["easyEnemy"] = "img/easy_enemy.png";
	spritePaths["hardEnemy"] = "img/hard_enemy.png";
	spritePaths["playerDeath"] = "img/player_death.png";
	spritePaths["playerMoveDown"] = "img/player_move_down.png";
	spritePaths["playerMoveUp"] = "img/player_move_up.png";
	spritePaths["playerMoveLeft"] = "img/player_move_left.png";
	spritePaths["playerMoveRight"] = "img/player_move_right.png";
	spritePaths["hud"] = "img/hud.png";
	spritePaths["menuScreen"] = "img/menu_screen.png";
	spritePaths["levelIntroScreen"] = "img/level_intro_screen.png";
	spritePaths["defeatScreen"] = "img/defeat_screen.png";
	spritePaths["powerUps"] = "img/power_ups.png";
	spritePaths["block"] = "img/block.png";
	spritePaths["whiteBlock"] = "img/whiteBlock.png";
	spritePaths["wallTop"] = "img/wallTop.png";
	spritePaths["wallLeft"] = "img/wallLeft.png";
	spritePaths["wallRight"] = "img/wallRight.png";
	spritePaths["wallDown"] = "img/wallDown.png";
	spritePaths["wallTopLeft"] = "img/wallTopLeft.png";
	spritePaths["wallTopRight"] = "img/wallTopRight.png";
	spritePaths["grass"] = "img/grass.png";
	spritePaths["blockBreaking"] = "img/block_breaking.png";
	spritePaths["arrow"] = "img/arrow.png";
}

void Textures::create_textures()
{
	for (const auto& path : spritePaths)
	{
		std::string spritePath = spritePaths[path.first];
		const char* c = spritePath.c_str();

		SDL_Surface* surface = IMG_Load(c);
		if (!surface) {
			std::cout << "Cant load m_texture with path: " << path.first << std::endl;
		}
		else
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
			SDL_FreeSurface(surface);
			textures[path.first] = texture;
		}
	}
}

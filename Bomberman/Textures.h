#pragma once
#include <string>
#include <map>
#include <SDL.h>

class Textures
{
public:
	Textures(SDL_Renderer* renderer);
	~Textures() = default;
	SDL_Texture* findTexture(std::string name);
private:
	SDL_Renderer* m_renderer;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, std::string> spritePaths;
	void save_sprite_paths();
	void create_textures();
};

#pragma once
#include <SDL.h>
#include <string>
#include <map>
#include "Config.h"
#include "Flame.h"
#include <utility>
#include <vector>
#include "Helpers.h"
#include "Enemy.h"
#include <SDL_mixer.h>

class Map;
class Enemy;
static const int BOMB_WIDTH = Config::BLOCK_WIDTH;
static const int BOMB_HEIGHT = Config::BLOCK_HEIGHT;

class Bomb
{
public:
	Bomb(int flamePower, int posX, int posY, sp<Map> map) : m_flamePower(flamePower), m_posX(posX), m_posY(posY), m_map(
		std::move(map))
	{
		spritePaths["bomb"] = "img/bomb.png";
		spritePaths["explosionCenter"] = "img/flame_center.png";
		windowRect = { posX, posY, BOMB_WIDTH, BOMB_HEIGHT };
		textureRect = { 0,0, BOMB_WIDTH, BOMB_HEIGHT };
		timeDropped = SDL_GetTicks();
		index_x = Helpers::GetCurrentBlock(m_posX, m_posY).first;
		index_y = Helpers::GetCurrentBlock(m_posX, m_posY).second;
		collider.x = posX;
		collider.y = posY;
	};
	~Bomb();
	bool isExploded = false;
	void render(SDL_Renderer* renderer);
	void load_textures(SDL_Renderer* renderer, const std::string &sprite);
	SDL_Rect collider = { 0,0, Config::BLOCK_WIDTH, Config::BLOCK_HEIGHT };
	bool hitFlame = false;
	bool firstCollision = true;
	std::vector<Enemy*> const enemyFirstCollision = {};
private:
	Uint32 timeDropped = 0;
	Uint32 timeExploded = 0;
	Uint32 bombTimer = 1500;
	Uint32 currentTime = 0;
	Uint32 oldTime = 0;
	bool explosionSound = false;
	int explosion_frame = 0;
	SDL_Texture* texture = nullptr;
	SDL_Rect windowRect;
	SDL_Rect textureRect;
	int m_flamePower = 0;
	int m_posX = 0;
	int m_posY = 0;
	sp<Map> m_map = nullptr;
	int index_x = 0;
	int index_y = 0;
	Mix_Chunk* m_chunk = Mix_LoadWAV("sounds/bomb.wav");

	std::vector<sp<Flame>> flames = {};
	std::map<std::string, std::string> spritePaths;

	void explode(SDL_Renderer* renderer);
	void renderFlames(SDL_Renderer* renderer, int frames);
	static bool canSpawnFlame(const sp<Map> &map, int index_x, int index_y);
};

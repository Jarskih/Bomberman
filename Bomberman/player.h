#pragma once
#include <SDL.h>
#include <vector>
#include "Helpers.h"
#include "Bomb.h"
#include "Entity.h"
#include "Config.h"

class Bomb;

class Player : public Entity {
public:
	Player(SDL_Renderer* renderer) : m_renderer(renderer) {
		m_pos_x = Config::BLOCK_WIDTH + Config::BLOCK_WIDTH / 2.0f;
		m_pos_y = Config::BLOCK_HEIGHT + Config::BLOCK_HEIGHT / 2.0f;
		m_type = PLAYER;
		m_is_alive = true;
		m_visible = true;
		m_collider = { 0, 0, Config::PLAYER_WIDTH / 3, Config::PLAYER_HEIGHT / 3 };
		m_windowRect = { 0, 0, Config::PLAYER_WIDTH, Config::PLAYER_HEIGHT };
		m_textureRect = { 0, 0, 0, 0 };
		m_state = IDLE_DOWN;
		m_speed_x = 0;
		m_speed_y = 0;
	};
	Player() = delete;
	~Player() = default;
	void update() override;
	void render() override;
	void handleEvent(SDL_Event& event);
	void die();
private:
	std::vector<sp<Bomb>> checkBombs();
	void playerController();
	void movePlayer();
	void renderBombs();
	void dropBomb();
	void animate();

public:
	bool m_moving = false;
	int m_speed = 3;
	int m_flame_power = 1;
	int m_max_bombs = 1;
	int m_lives = Config::STARTING_LIVES;
	std::vector<sp<Bomb>> m_bombs = {};
	int m_bombs_dropped = 0;
	int m_old_state = 0;
private:
	std::string m_texture_name = "playerMoveDown";
	SDL_Texture* loadTexture();
	SDL_Renderer* m_renderer = nullptr;
	SDL_Rect m_window_rect = { 0, 0, Config::PLAYER_WIDTH, Config::PLAYER_HEIGHT };
	SDL_Rect m_texture_rect = {};
	SDL_Texture* m_texture = nullptr;
	int m_frame = 0;
	Uint32 m_time_died = 0;
	Uint32 m_old_time = 0;
	Uint32 m_delay_per_frame = 100;
};

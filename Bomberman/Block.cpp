#include "Block.h"
#include <SDL.h>
#include "PowerUp.h"
#include "Map.h"

using namespace Config;

std::pair <int, int> Block::getBlockIndex() const
{
	return Helpers::GetCurrentBlock(m_pos_x, m_pos_y);
}

void Block::getSprite()
{
	switch (m_block_type) {
	case BREAKABLE:
		m_sprite = "img/block.png";
		break;
	case NONBREAKABLE:
		m_sprite = "img/whiteBlock.png";
		break;
	case WALL_UP:
		m_sprite = "img/wallTop.png";
		break;
	case WALL_LEFT:
		m_sprite = "img/wallLeft.png";
		break;
	case WALL_RIGHT:
		m_sprite = "img/wallRight.png";
		break;
	case WALL_DOWN:
		m_sprite = "img/wallDown.png";
		break;
	case WALL_LEFT_UP:
		m_sprite = "img/wallTopLeft.png";
		break;
	case WALL_RIGHT_UP:
		m_sprite = "img/wallTopRight.png";
		break;
	case WALL_LEFT_DOWN:
		m_sprite = "img/wallDown.png";
		break;
	case WALL_RIGHT_DOWN:
		m_sprite = "img/wallDown.png";
		break;
	case GRASS:
		m_sprite = "img/grass.png";
		break;
	case DESTROYED:
		m_sprite = "img/block_breaking.png";
		break;
	default:
		m_sprite = "error";
		break;
	}
}
/*
SDL_Texture* Block::LoadTexture(SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;
	GetSprite();

	if (m_sprite == "error") {
		std::cout << "Error loading sprite" << std::endl;
	}

	SDL_Surface* surface = IMG_Load(m_sprite);
	if (!surface) {
		std::cout << "Cant load block: " << blockType << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
*/

void Block::LoadTexture() {
	switch (m_block_type) {
	case BREAKABLE:
		m_texture = m_textures->findTexture("block");
		break;
	case NONBREAKABLE:
		m_texture = m_textures->findTexture("whiteBlock");
		break;
	case WALL_UP:
		m_texture = m_textures->findTexture("wallTop");
		break;
	case WALL_LEFT:
		m_texture = m_textures->findTexture("wallLeft");
		break;
	case WALL_RIGHT:
		m_texture = m_textures->findTexture("wallRight");
		break;
	case WALL_DOWN:
		m_texture = m_textures->findTexture("wallDown");
		break;
	case WALL_LEFT_UP:
		m_texture = m_textures->findTexture("wallTopLeft");
		break;
	case WALL_RIGHT_UP:
		m_texture = m_textures->findTexture("wallTopRight");
		break;
	case WALL_LEFT_DOWN:
		m_texture = m_textures->findTexture("wallDown");
		break;
	case WALL_RIGHT_DOWN:
		m_texture = m_textures->findTexture("wallDown");
		break;
	case GRASS:
		m_texture = m_textures->findTexture("grass");
		break;
	case DESTROYED:
		m_texture = m_textures->findTexture("blockBreaking");
		break;
	default:
		break;
	}
}

void Block::render(SDL_Renderer* renderer) {
	/*
	if (blockType == DESTROYED && !textureLoaded)
	{
		SDL_DestroyTexture(m_texture);
		LoadTexture();
		textureLoaded = true;
	}
	else if (blockType != DESTROYED && !textureLoaded)
	{
		SDL_DestroyTexture(m_texture);
		LoadTexture();
		textureLoaded = true;
	}
	else if (blockType == GRASS && !textureLoaded) {
		SDL_DestroyTexture(m_texture);
		LoadTexture();
		textureLoaded = true;
	}*/

	if (m_old_block_type != m_block_type)
	{
		LoadTexture();
		m_old_block_type = m_block_type;
	}

	m_window_rect.x = m_pos_x;
	m_window_rect.y = m_pos_y;
	m_collider.x = m_pos_x;
	m_collider.y = m_pos_y;

	const int totalFrames = 7;
	if (m_block_type == DESTROYED)
	{
		if (m_block_has_power_up && !m_power_up_added) {
			auto map = Service<Map>::Get();
			map->addPowerUp(m_index_x, m_index_y, m_power_up_type);
			m_power_up_added = true;
		}

		const int delayPerFrame = 100;

		if (SDL_GetTicks() - timeExploded > delayPerFrame)
		{
			m_texture_rect.y = m_frame * m_texture_rect.h;
			SDL_QueryTexture(m_texture, nullptr, nullptr, &m_texture_rect.w, &m_texture_rect.h);

			m_texture_rect.h /= totalFrames;
			m_frame++;
		}
		if (m_frame >= totalFrames - 1)
		{
			changeBlockType(GRASS);
		}
		SDL_RenderCopy(renderer, m_texture, &m_texture_rect, &m_window_rect);
	}
	else
	{
		SDL_RenderCopy(renderer, m_texture, nullptr, &m_window_rect);
	}

}

void Block::changeBlockType(int newType)
{
	m_block_type = newType;
	m_texture_loaded = false;
	timeExploded = SDL_GetTicks();
}

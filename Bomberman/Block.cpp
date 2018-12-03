#include "Block.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

void Block::GetSprite()
{
	switch (m_blockType) {
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
		// TODO add block
		break;
	default:
		m_sprite = "error";
		break;
	}
}

SDL_Texture* Block::LoadTexture(SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;
	GetSprite();

	if (m_sprite == "error") {
		std::cout << "Error loading sprite" << std::endl;
	}

	SDL_Surface* surface = IMG_Load(m_sprite);
	if (!surface) {
		std::cout << "Cant load block: " << m_blockType << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void Block::render(SDL_Renderer* renderer) {
	if (isDestroyed && !destroyedTextureLoaded)
	{
		m_blockType = DESTROYED;
		SDL_DestroyTexture(texture);
		texture = LoadTexture(renderer);
		destroyedTextureLoaded = true;
	}
	else if (!isDestroyed && !textureLoaded)
	{
		SDL_DestroyTexture(texture);
		texture = LoadTexture(renderer);
		textureLoaded = true;
	}

	windowRect.x = m_x;
	windowRect.y = m_y;

	SDL_RenderCopy(renderer, texture, nullptr, &windowRect);
}

#include "Block.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Flame.h"

std::pair <int, int> Block::getBlockIndex()
{
	return Helpers::getCurrentBlock(m_pos_x, m_pos_y);
}

void Block::GetSprite()
{
	switch (blockType) {
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

void Block::render(SDL_Renderer* renderer) {
	if (blockType == DESTROYED && !textureLoaded)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = LoadTexture(renderer);
		textureLoaded = true;
	}
	else if (blockType != DESTROYED && !textureLoaded)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = LoadTexture(renderer);
		textureLoaded = true;
	}
	else if (blockType == GRASS && !textureLoaded) {
		SDL_DestroyTexture(m_texture);
		m_texture = LoadTexture(renderer);
		textureLoaded = true;
	}

	windowRect.x = m_pos_x;
	windowRect.y = m_pos_y;
	collider.x = m_pos_x;
	collider.y = m_pos_y;

	const int totalFrames = 7;
	if (blockType == DESTROYED)
	{
		const int delayPerFrame = 100;

		if (SDL_GetTicks() - timeExploded > delayPerFrame)
		{
			textureRect.y = frame * textureRect.h;
			SDL_QueryTexture(m_texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

			textureRect.h /= totalFrames;
			frame++;
		}
		if (frame >= totalFrames - 1)
		{
			changeBlockType(GRASS);
		}
		SDL_RenderCopy(renderer, m_texture, &textureRect, &windowRect);
	}
	else
	{
		SDL_RenderCopy(renderer, m_texture, nullptr, &windowRect);
	}


	//SDL_RenderDrawRect(renderer, &collider);
}

void Block::changeBlockType(int newType)
{
	blockType = newType;
	textureLoaded = false;
	timeExploded = SDL_GetTicks();
}

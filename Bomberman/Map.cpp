#include "Map.h"

void Map::render(SDL_Renderer * renderer)
{
	for (auto block : m_tileSet) {
		block->render(renderer);
	}
}

void Map::generateMap() {
	for (int y = 0; y < size_Y; y++) {
		for (int x = 0; x < size_X; x++) {
			int posX = x * BLOCK_WIDTH;
			int posY = y * BLOCK_HEIGHT;
			m_tileSet.emplace_back(mksp<Block>(posX, posY, blockTypes[y][x]));
		}
	}
}


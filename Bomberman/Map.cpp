#include "Map.h"
#include "player.h"

void Map::render()
{
	for (const auto& block : tileSet) {
		block->render(m_renderer);
	}
}

void Map::generateMap() {
	for (int y = 0; y < m_size_Y; y++) {
		for (int x = 0; x < m_size_X; x++) {
			int posX = x * BLOCK_WIDTH;
			int posY = y * BLOCK_HEIGHT;
			tileSet.emplace_back(makesp<Block>(posX, posY, MAP_LAYOUT[y][x]));
		}
	}
}

void Map::loadTextures()
{
	for (const auto& block : tileSet)
	{
		block->LoadTexture(m_renderer);
	}
}

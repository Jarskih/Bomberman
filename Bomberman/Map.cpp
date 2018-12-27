#include "Map.h"
#include "player.h"
#include "EasyEnemy.h"

void Map::update(sp<Map> &map) const
{
	for (const auto& player : m_playerList)
	{
		player->update(map);
	}

	for (const auto& enemy : m_enemyList)
	{
		enemy->update(map);
	}
}

void Map::render(sp<Map> &map) const
{
	for (const auto& block : tileSet) {
		block->render(m_renderer);
	}

	for (const auto& player : m_playerList)
	{
		player->render(map);
	}

	for (const auto& enemy : m_enemyList)
	{
		enemy->render(map);
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
void Map::spawnGameObjects()
{
	auto player = makesp<Player>(m_renderer);
	m_playerList.push_back(player);

	auto enemy1 = makesp<EasyEnemy>(m_renderer, 11, 6);
	auto enemy2 = makesp<EasyEnemy>(m_renderer, 9, 8);
	auto enemy3 = makesp<EasyEnemy>(m_renderer, 3, 6);
	m_enemyList.push_back(enemy1);
	m_enemyList.push_back(enemy2);
	m_enemyList.push_back(enemy3);
}


void Map::loadTextures()
{
	for (const auto& block : tileSet)
	{
		block->LoadTexture(m_renderer);
	}
}

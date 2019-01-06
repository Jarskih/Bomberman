#pragma once
#include <unordered_map>
#include <list>
#include "Helpers.h"
#include "Block.h"
#include "Map.h"

namespace Pathfinding {
	inline std::list<sp<Block>> discoverNeighbors(sp<Block> &block)
	{
		std::list<sp<Block>> neighbors = {};
		auto map = Service<Map>::Get();

		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				const int checkX = block->index_x + x;
				const int checkY = block->index_y + y;

				if (checkX >= 0 && checkX < MAX_BLOCKS_X && checkY >= 0 && checkY < MAX_BLOCKS_Y)
				{
					neighbors.push_front(map->tileSet[checkX][checkY]);
				}
			}
		}
		return neighbors;
	}

	inline int getDistance(sp<Block> &target, sp<Block> &start)
	{
		const int distX = target->index_x - start->index_x;
		const int distY = target->index_y - start->index_y;

		if (distX > distY)
		{
			return 14 * distY + 10 * (distX - distY);
		}
		else
		{
			return 14 * distX + 10 * (distY - distX);
		}
	}

	inline void retracePath(sp<Block> &start, sp<Block> &end)
	{
		std::list<sp<Block>> path = {};
		sp<Block> current = end;

		while (current != start)
		{
			path.emplace_front(current);
			current = current->parent;
		}

		path.reverse();
	}


	inline void calculatePath(sp<Block> target, sp<Block> start)
	{

		std::list<sp<Block>> open;
		std::unordered_map<std::pair<int, int>, sp<Block>> closed;

		open.push_front(start);

		while (!open.empty())
		{
			sp<Block> current = open.front();

			// Find closest block to target from start
			for (const auto &block : open)
			{
				if (block->fCost() < current->fCost() || block->fCost() == current->fCost() && block->hCost < current->hCost)
				{
					current = block;
				}
			}

			// remove current block from open;
			open.pop_front();
			// add current block to closed
			std::pair<int, int> currentIndex = { current->m_pos_x, current->m_pos_y };
			closed.emplace(currentIndex, current);

			if (current == target)
			{
				retracePath(start, target);
				return;
			}

			for (auto &neighbor : discoverNeighbors(current))
			{
				std::pair<int, int> blockIndex = { neighbor->index_x, neighbor->index_y };
				// if block is not walkable or it is already in closed set
				auto it = closed.find(blockIndex);
				if (neighbor->blockType != GRASS || it != closed.end())
				{
					continue;
				}

				const int newCostToNeighbor = current->gCost + getDistance(current, neighbor);
				//if new path to neighbor is shorter or neighbor is not in open
				if (newCostToNeighbor < neighbor->gCost || std::find(open.begin(), open.end(), neighbor) != open.end())
				{
					neighbor->gCost = newCostToNeighbor;
					neighbor->hCost = getDistance(neighbor, target);
					neighbor->parent = current;

					if (std::find(open.begin(), open.end(), neighbor) != open.end())
					{
						open.push_front(neighbor);
					}
				}
			}
		}
	}
}

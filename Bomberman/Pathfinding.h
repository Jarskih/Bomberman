#pragma once
#include <vector>
#include "Helpers.h"
#include "Block.h"

class Node
{
public:
	int index_x = 0;
	int index_y = 0;
	int f_cost = 0;
	int g_cost = 0;
	Node* parent = nullptr;
	std::vector<Node> neighbors = {};

	void discoverNeighbors() {};
};

sp<Node> findLowestCost(std::vector<sp<Node>> open)
{
	int f_cost = 0;
	for (const auto& node : open)
	{
		if (f_cost > node->f_cost)
		{
			f_cost = node->f_cost;
		}
	}
}

void removeNode()
{

}

void addNode()
{

}

void calculatePath(sp<Node> target, sp<Node> start)
{
	std::vector<sp<Node>> open;
	std::vector<sp<Node>> closed;

	auto node = makesp<Node>(start->index_x, start->index_y);
	bool done = false;

	sp<Node> current = nullptr;

	while (!done)
	{
		current = findLowestCost(open);
		// remove current from open;
		// add current to closed

		if (current == target)
		{

		}
	}
}

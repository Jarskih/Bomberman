#include "Helpers.h"
#include "GameRules.h"
#include <iostream>

// Get block center coordinates from indexes
std::pair<int, int> getBlockCenter(int index_x, int index_y)
{
	const int x = index_x * BLOCK_WIDTH; // + BLOCK_OFFSET_X;
	const int y = index_y * BLOCK_HEIGHT; // + BLOCK_OFFSET_Y;

	std::pair<int, int> blockCenter;
	blockCenter.first = x - 1;
	blockCenter.second = y - 1;
	return blockCenter;
}

// Get block index from coordinates
std::pair<int, int> getCurrentBlock(int x, int y)
{
	const int index_x = (x / BLOCK_WIDTH) + 1;
	const int index_y = (y / BLOCK_HEIGHT) + 1;

	std::pair<int, int> blockIndexes;
	blockIndexes.first = index_x;
	blockIndexes.second = index_y;
	return blockIndexes;
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool isOutOfGameArea(SDL_Rect a, SDL_Rect border) {
	//The sides of the rectangles
	int leftA, leftBorder;
	int rightA, rightBorder;
	int topA, topBorder;
	int bottomA, bottomBorder;

	//Calculate the sides of rect A
	leftA = a.x + a.w;
	rightA = a.x;
	topA = a.y + a.h;
	bottomA = a.y;

	//Calculate the sides of rect B
	leftBorder = border.x;
	rightBorder = border.x + border.w;
	topBorder = border.y;
	bottomBorder = border.y + border.h;
	if (bottomA <= topBorder)
	{
		return true;
	}

	if (topA >= bottomBorder)
	{
		return true;
	}

	if (rightA <= leftBorder)
	{
		return true;
	}

	if (leftA >= rightBorder)
	{
		return true;
	}

	//If none of the sides from A are outside B
	return false;
}

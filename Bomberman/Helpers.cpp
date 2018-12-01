#include "Helpers.h"

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

bool isOutOfGamearea(SDL_Rect a, SDL_Rect border) {
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

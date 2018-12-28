#pragma once
#include <SDL.h>
#include <memory>

namespace Helpers {
	std::pair<int, int> getBlockCenter(int index_x, int index_y);
	std::pair<int, int> getCurrentBlock(int x, int y);
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	bool isOutOfGameArea(SDL_Rect a, SDL_Rect b);

}
template <class T> using sp = std::shared_ptr<T>;

template <typename T, typename... Arguments> sp<T> makesp(Arguments &&... arguments)
{
	return std::make_shared<T>(std::forward<Arguments>(arguments)...);
}

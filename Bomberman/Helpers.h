#pragma once
#include <SDL.h>
#include <memory>


bool checkCollision(SDL_Rect a, SDL_Rect b);
bool isOutOfGamearea(SDL_Rect a, SDL_Rect b);
template <class T> using sp = std::shared_ptr<T>;

template <typename T, typename... Arguments> sp<T> mksp(Arguments &&... arguments)
{
	return std::make_shared<T>(std::forward<Arguments>(arguments)...);
}

#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include <iostream>
#include "GameRules.h"

SDL_Texture* drawBackground(SDL_Renderer* renderer) {
	SDL_Texture* background = nullptr;
	SDL_Surface* temp = IMG_Load("img/game_bkg1.png");
	if (!temp) {
		std::cout << "Cant load background" << std::endl;
	}
	background = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	return background;
}

//For SDL, you should have the following main method:
int main(int argc, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//For loading PNG images
	IMG_Init(IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event input;
	bool quit = false;

	SDL_Texture* background = drawBackground(renderer);
	SDL_Rect bgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	Player* player = new Player();

	while (!quit)
	{
		while (SDL_PollEvent(&input) > 0)
		{
			if (input.type == SDL_QUIT)
			{
				quit = true;
			}
			player->handleEvent(input);
		}

		player->movePlayer();
		player->animate();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background, NULL, &bgRect);

		player->render(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

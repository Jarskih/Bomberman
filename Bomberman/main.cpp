#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Player.h"
#include <iostream>
#include "GameRules.h"
#include "Musicplayer.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event input;
SDL_Rect bgRect;
SDL_Rect bgCollider;
SDL_Texture* background = nullptr;

void drawBackground() {
	SDL_Surface* temp = IMG_Load("img/game_bkg1.png");
	if (!temp) {
		std::cout << "Cant load background" << std::endl;
	}
	background = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);
	bgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	bgCollider = { 60, 100, 680, 440 };
}

void SDLinit() {
	SDL_Init(SDL_INIT_EVERYTHING);
	//For loading PNG images
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

//For SDL, you should have the following main method:
int main(int argc, char** args)
{
	bool quit = false;

	SDLinit();

	Player* player = new Player();

	drawBackground();
	InitMusicPlayer();
	PlayMusic();

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

		player->movePlayer(bgCollider);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background, NULL, &bgRect);

		player->render(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &bgCollider);
		SDL_RenderDrawRect(renderer, &player->collider);

		SDL_RenderPresent(renderer);
	}
	DestroyMusicPlayer();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

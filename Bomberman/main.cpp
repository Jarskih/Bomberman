#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include "Helpers.h"
#include "player.h"
#include "GameRules.h"
#include "Musicplayer.h"
#include "Map.h"
#include "Timer.h"
#include "Textures.h"
#include "Service.h"

SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
SDL_Event input;

void SDLinit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());

	if (Mix_Init(MIX_INIT_MP3) == 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL_mixer: %s", Mix_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize OpenAudio: %s", Mix_GetError());

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize IMG: %s", IMG_GetError());

	window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Window: %s", SDL_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Renderer: %s", SDL_GetError());
}

//For SDL, you should have the following main method:
int main(int argc, char** args)
{
	SDLinit();

	{
		auto map = makesp<Map>(13, 15, renderer);
		auto timer = makesp<Timer>();
		auto player = makesp<Player>(renderer);
		auto textures = makesp<Textures>(renderer);
		Service<Textures>::Set(textures);

		SDL_Rect temp = { 0, 0 ,0, 0 };

		InitMusicPlayer();

		map->loadTextures();
		timer->start();

		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&input) > 0)
			{
				if (input.type == SDL_QUIT)
				{
					quit = true;
				}
				//player->handleEvent(input);
			}

			// Clear screen
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			// Update

			player->playerController(map);
			player->movePlayer(map->tileSet);
			timer->start();

			map->render();

			// Debug
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			player->update(map);

			// Debug
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			SDL_RenderDrawRect(renderer, &player->collider);


			// Presenting to screen
			SDL_RenderPresent(renderer);
		}
	}
	DestroyMusicPlayer();

	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	if (window != nullptr)
		SDL_DestroyWindow(window);

	IMG_Quit();

	Mix_CloseAudio();

	Mix_Quit();

	SDL_Quit();

	return 0;
}

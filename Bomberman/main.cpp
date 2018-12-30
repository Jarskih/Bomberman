#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include "Helpers.h"
#include "GameRules.h"
#include "Musicplayer.h"
#include "Map.h"
#include "Timer.h"
#include "Service.h"
#include "Textures.h"
#include "Hud.h"
#include "State.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event input;

void SDLInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
	}
	if (Mix_Init(MIX_INIT_MP3) == 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL_mixer: %s", Mix_GetError());
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize OpenAudio: %s", Mix_GetError());
	}
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize IMG: %s", IMG_GetError());
	}
	if (TTF_Init() == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Window: %s", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Renderer: %s", SDL_GetError());
	}
}

void handleEvent(const SDL_Event event, const sp<State>& state)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			state->changeScene();
			break;
		default:
			break;
		}
	}
}

//For SDL, you should have the following main method:
int main(int argc, char** args)
{
	SDLInit();
	auto gameState = makesp<State>();
	Service<State>::Set(gameState);
	SDL_Rect fullScreen = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	SDL_Texture* bgTexture;

	const auto textures = makesp<Textures>(renderer);
	Service<Textures>::Set(textures);

	bool quit = false;
	while (!quit) {

		while (SDL_PollEvent(&input) > 0)
		{
			if (input.type == SDL_QUIT) {
				quit = true;
			}
			handleEvent(input, gameState);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		if (gameState->lives < 0)
		{
			gameState->scene = State::DEFEAT;
		}

		switch (gameState->scene) {
		case State::MENU:
			bgTexture = textures->findTexture("menuScreen");
			SDL_RenderCopy(renderer, bgTexture, nullptr, &fullScreen);
			SDL_RenderPresent(renderer);
			break;
		case State::LEVEL_INTRO:
			bgTexture = textures->findTexture("levelIntroScreen");
			SDL_RenderCopy(renderer, bgTexture, nullptr, &fullScreen);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000);
			gameState->scene = State::LEVEL;
			break;
		case State::DEFEAT:
			bgTexture = textures->findTexture("defeatScreen");
			SDL_RenderCopy(renderer, bgTexture, nullptr, &fullScreen);
			SDL_RenderPresent(renderer);
			break;
		case State::LEVEL:
		{
			auto timer = makesp<Timer>();
			timer->start();
			Service<Timer>::Set(timer);

			auto map = makesp<Map>(14, 15, renderer);
			map->loadTextures();
			Service<Map>::Set(map);

			auto hud = makesp<Hud>(renderer, textures->findTexture("hud"));
			Service<Hud>::Set(hud);

			MusicPlayer::InitMusicPlayer();

			bool restart = false;
			while (!restart)
			{
				while (SDL_PollEvent(&input) > 0)
				{
					map->handleEvent(input);
				}

				// Clear screen
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderClear(renderer);

				// Update
				map->update(timer);

				// Render
				map->render(map);
				hud->render(timer);

				// Presenting to screen
				SDL_RenderPresent(renderer);

				SDL_Delay(16);

				for (const auto& player : map->m_playerList)
				{
					if (player->isDead)
					{
						gameState->lives--;
						restart = true;
						gameState->scene = State::LEVEL_INTRO;
					}
				}
			}
		}
		break;
		default:
			break;
		}
	}
	MusicPlayer::DestroyMusicPlayer();

	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	if (window != nullptr)
		SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();

	return 0;
}

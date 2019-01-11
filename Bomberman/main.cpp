#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include "Helpers.h"
#include "Config.h"
#include "Musicplayer.h"
#include "Map.h"
#include "Timer.h"
#include "Service.h"
#include "Textures.h"
#include "Hud.h"
#include "State.h"
#include <SDL_mixer.h>
#include <ctime>
#include "GUIArrow.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

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

	window = SDL_CreateWindow("Dynablaster (amiga version). Use arrow keys to move, space for dropping bomb and left CTRL for debug mode.", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Window: %s", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Renderer: %s", SDL_GetError());
	}
}

void handleEvent(const SDL_Event event, const sp<State> &state, sp<GUIArrow> &arrow)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:

		case SDLK_ESCAPE:
			state->goToMenu();
		case SDLK_LCTRL:
			state->toggleDebug();
			break;
		case SDLK_SPACE:
			state->sceneTransition(arrow);
			break;
		case SDLK_KP_ENTER:
			state->sceneTransition(arrow);
			break;
		case SDLK_DOWN:
			arrow->down();
			break;
		case SDLK_UP:
			arrow->up();
			break;
		default:
			break;
		}
	}
}

int main(int argc, char** args)
{
	SDL_Event input;

	SDLInit();
	auto gameState = makesp<State>();
	Service<State>::Set(gameState);

	const auto textures = makesp<Textures>(renderer);
	Service<Textures>::Set(textures);

	auto arrow = makesp<GUIArrow>(textures);

	SDL_Texture* bgTexture;
	SDL_Rect fullScreen = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	MusicPlayer::InitMusicPlayer();

	bool quit = false;
	while (!quit) {

		if (gameState->m_scene != State::DEFEAT && gameState->m_lives < 0)
		{
			gameState->changeScene(State::DEFEAT);
			gameState->m_lives = STARTING_LIVES;
		}

		while (SDL_PollEvent(&input) > 0)
		{
			if (input.type == SDL_QUIT) {
				quit = true;
			}
			handleEvent(input, gameState, arrow);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		switch (gameState->m_scene) {
		case State::MENU:
			gameState->m_score = 0;
			bgTexture = textures->findTexture("menuScreen");
			SDL_RenderCopy(renderer, bgTexture, nullptr, &fullScreen);
			arrow->update(gameState);
			SDL_RenderCopy(renderer, arrow->m_texture, nullptr, &arrow->m_window_rect);
			SDL_RenderPresent(renderer);
			break;
		case State::LEVEL_INTRO:
			bgTexture = textures->findTexture("levelIntroScreen");
			SDL_RenderCopy(renderer, bgTexture, nullptr, &fullScreen);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);
			gameState->changeScene(State::LEVEL);
			break;
		case State::DEFEAT:
			gameState->m_score = 0;
			bgTexture = textures->findTexture("defeatScreen");
			SDL_RenderCopy(renderer, bgTexture, nullptr, &fullScreen);
			arrow->update(gameState);
			SDL_RenderCopy(renderer, arrow->m_texture, nullptr, &arrow->m_window_rect);
			SDL_RenderPresent(renderer);
			break;
		case State::LEVEL:
		{
			srand(time(nullptr));
			auto timer = makesp<Timer>();
			timer->start();
			Service<Timer>::Set(timer);

			auto map = makesp<Map>(renderer);
			Service<Map>::Set(map);

			auto hud = makesp<Hud>(renderer);
			Service<Hud>::Set(hud);

			MusicPlayer::PlayMusic();

			bool restart = false;
			while (!restart)
			{
				while (SDL_PollEvent(&input) > 0)
				{
					handleEvent(input, gameState, arrow);
					map->handleEvent(input);
				}

				// Clear screen
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderClear(renderer);

				// update
				map->update(timer);

				// Render
				map->render(map);
				hud->render(timer);

				// Presenting to screen
				SDL_RenderPresent(renderer);

				SDL_Delay(16);

				for (const auto& player : map->m_playerList)
				{
					if (!player->isAlive())
					{
						gameState->decrementLives();
						restart = true;
						gameState->changeScene(State::LEVEL_INTRO);
					}
				}

				if (map->m_level_cleared)
				{
					if (gameState->m_level == 1)
					{
						gameState->nextLevel();
						restart = true;
					}
					else
					{
						gameState->goToMenu();
						restart = true;
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

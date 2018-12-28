#include "Musicplayer.h"
#include <iostream>

namespace MusicPlayer {

	Mix_Music* gMusic;

	//Initialize SDL_mixer
	void InitMusicPlayer() {
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
			std::cout << "Could not start music player" << std::endl;
		}
		else
		{
			PlayMusic();
		}
	}

	//Load music
	void PlayMusic() {
		gMusic = Mix_LoadMUS("sounds/music.mp3");
		if (gMusic == nullptr)
		{
			printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		}
		else {
			Mix_PlayMusic(gMusic, -1);
		}
	}

	void PlaySound(const char* filePath)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(filePath);
		Mix_PlayChannel(-1, chunk, 0);
	}

	void DestroyMusicPlayer() {
		Mix_FreeMusic(gMusic);
		gMusic = nullptr;
	}

}

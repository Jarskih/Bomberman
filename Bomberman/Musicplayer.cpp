#include "Musicplayer.h"


Mix_Music* gMusic;

//Initialize SDL_mixer
bool InitMusicPlayer() {
	return Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

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

void DestroyMusicPlayer() {
	Mix_FreeMusic(gMusic);
	gMusic = nullptr;
}

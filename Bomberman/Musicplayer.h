#pragma once
#include <SDL_mixer.h>
#include <stdio.h>

namespace MusicPlayer {
	void InitMusicPlayer();
	void PlayMusic();
	void PlaySound(const char* filePath);
	void DestroyMusicPlayer();
}


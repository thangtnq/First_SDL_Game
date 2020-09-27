#pragma once

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

const int HEIGHT = 600;
const int WIDTH = 1200;
const int BPP = 32;
const int NUM_THREAT = 3;
const int BG_WIDTH = 4800;
const int BG_HEIGHT = 600;

extern SDL_Surface* g_screen;
extern SDL_Surface* g_background;
extern SDL_Event g_event;

extern Mix_Chunk* g_sound_bullet[2];
extern Mix_Chunk* g_sound_exp[2];


namespace SDLCommonFunc
{
	bool Init();
	SDL_Surface* LoadImage(std::string filePath);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, const int& x, const int& y);
	void CleanUp();
	bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, const int& x, const int& y);
}


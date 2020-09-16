#pragma once

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

const int HEIGHT = 600;
const int WIDTH = 1200;
const int BPP = 32;
const int NUM_THREAT = 3;

extern SDL_Surface* g_screen;
extern SDL_Surface* g_background;
extern SDL_Event g_event;

namespace SDLCommonFunc
{
	bool Init();
	SDL_Surface* LoadImage(std::string filePath);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, const int& x, const int& y);
	void CleanUp();
}


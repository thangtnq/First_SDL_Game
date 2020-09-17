#pragma once

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

const int HEIGHT = 600;
const int WIDTH = 1200;
const int BPP = 32;
const int NUM_THREAT = 3;
const int BG_WIDTH = 4800;
const int BG_HEIGHT = 600;

extern SDL_Surface* g_screen;
extern SDL_Surface* g_background;
extern SDL_Event g_event;

namespace SDLCommonFunc
{
	bool Init();
	SDL_Surface* LoadImage(std::string filePath);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, const int& x, const int& y);
	void CleanUp();
	bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}


#include "Common_Function.h"


SDL_Surface* g_screen = nullptr;
SDL_Surface* g_background = nullptr;
SDL_Event g_event;

SDL_Surface* SDLCommonFunc::LoadImage(std::string filePath)
{
	SDL_Surface* image = nullptr;
	SDL_Surface* optimize_image = nullptr;
	image = IMG_Load(filePath.c_str());
	if (image != nullptr)
	{
		optimize_image = SDL_DisplayFormat(image);
		SDL_FreeSurface(image);
		if (optimize_image != nullptr)
		{
			UINT32 color = SDL_MapRGB(optimize_image->format, 0, 0xff, 0xff);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color);
		}
	}
	return optimize_image;
}

void SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, const int& x, const int& y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}

void SDLCommonFunc::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_background);
}

bool SDLCommonFunc::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	g_screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
	if (g_screen == nullptr)
		return false;
	return true;
}
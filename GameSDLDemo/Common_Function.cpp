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

bool SDLCommonFunc::checkCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	struct CollisionObject
	{
		int left;
		int right;
		int top;
		int bottom;
	};

	CollisionObject aObject = { object1.x ,object1.x + object1.w, object1.y, object1.y + object1.h };
	CollisionObject bObject = { object2.x ,object2.x + object2.w, object2.y, object2.y + object2.h };

	//case 1: size object 1 < size object 2
	if (aObject.left > bObject.left&& aObject.left < bObject.right)
		if ((aObject.top > bObject.top&& aObject.top < bObject.bottom) 
			|| (aObject.bottom > bObject.top&& aObject.bottom < bObject.bottom))
			return true;

	if(aObject.right > bObject.left && aObject.right < bObject.right)
		if ((aObject.top > bObject.top&& aObject.top < bObject.bottom)
			|| (aObject.bottom > bObject.top&& aObject.bottom < bObject.bottom))
			return true;
	//case 2: size object 1 > size object 2
	if (bObject.left > aObject.left&& bObject.left < aObject.right)
		if ((bObject.top > aObject.top&& bObject.top < aObject.bottom)
			|| bObject.bottom > aObject.top&& bObject.bottom < aObject.bottom)
			return true;

	if(bObject.right > aObject.left && bObject.right < aObject.right)
		if ((bObject.top > aObject.top&& bObject.top < aObject.bottom)
			|| bObject.bottom > aObject.top&& bObject.bottom < aObject.bottom)
			return true;
	//case 3: same size
	if (aObject.top == bObject.top && aObject.right == bObject.right && aObject.bottom == bObject.bottom)
		return true;

	return false;
}

void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, const int& x, const int& y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}
#pragma once

#include "Common_Function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface* des);
	bool LoadIMG(const char* fileName);

	void SetRect(const int& x, const int& y) { rect.x = x; rect.y = y; }
	SDL_Rect GetRect() const { return rect; }
	SDL_Surface* GetObject() { return pObject; }
protected:
	SDL_Rect rect;
	SDL_Surface* pObject;
};


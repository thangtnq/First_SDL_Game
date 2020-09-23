#pragma once

#include "BaseObject.h"
#include "Common_Function.h"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;


class ExplosionObject : public BaseObject
{

public:
	ExplosionObject();
	~ExplosionObject();

	void setClip();
	void setFrame(const int& fr) { frame = fr; }
	void showEx(SDL_Surface* des);

private:
	int frame;
	SDL_Rect clip[4];
};


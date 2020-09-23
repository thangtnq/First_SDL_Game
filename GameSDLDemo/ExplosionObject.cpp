#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
	this->frame = 0;

}

ExplosionObject::~ExplosionObject() 
{}

void ExplosionObject::setClip()
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = EXP_WIDTH;
	clip[0].h = EXP_HEIGHT;

	clip[1].x = EXP_WIDTH;
	clip[1].y = 0;
	clip[1].w = EXP_WIDTH;
	clip[1].h = EXP_HEIGHT;

	clip[2].x = EXP_WIDTH*2;
	clip[2].y = 0;
	clip[2].w = EXP_WIDTH;
	clip[2].h = EXP_HEIGHT;

	clip[3].x = EXP_WIDTH*3;
	clip[3].y = 0;
	clip[3].w = EXP_WIDTH;
	clip[3].h = EXP_HEIGHT;
}

void ExplosionObject::showEx(SDL_Surface* des)
{
	if (this->frame >= 4)
		this->frame = 0;
	SDLCommonFunc::ApplySurfaceClip(this->pObject, des, &this->clip[this->frame], rect.x, rect.y);
}

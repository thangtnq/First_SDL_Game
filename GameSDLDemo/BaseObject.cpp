#include "BaseObject.h"

BaseObject::BaseObject()
{
	this->rect.x = 0;
	this->rect.y = 0;
	this->pObject = nullptr;
}

BaseObject::~BaseObject()
{
	if (this->pObject != nullptr)
		SDL_FreeSurface(this->pObject);
}

bool BaseObject::LoadIMG(const char* fileName)
{
	this->pObject = SDLCommonFunc::LoadImage(fileName);
	if (this->pObject == nullptr)
		return false;
	return true;
}

void BaseObject::Show(SDL_Surface* des)
{
	if (this->pObject != nullptr)
	{
		SDLCommonFunc::ApplySurface(this->pObject, des, rect.x, rect.y);
	}
}
#include "AmoObject.h"


AmoObject::AmoObject()
{
	this->rect.x = 0;
	this->rect.y = 0;
	xVal = 0;
	yVal = 0;
	isMove = false;
	amo_type = NONE;
}

AmoObject::~AmoObject()
{}

void AmoObject::HandleMoveRightToLeft()
{
	rect.x -= xVal;
	if (rect.x < 0)
		isMove = false;
	
}

void AmoObject::HandleMove(const int& xBorder, const int& yBorder)
{
	if (isMove)
	{
		rect.x += xVal;
		if (rect.x > xBorder)
			isMove = false;
	}	
}

void AmoObject::HandleInputAction(SDL_Event e)
{

}
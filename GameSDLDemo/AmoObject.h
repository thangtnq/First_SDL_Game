#pragma once

#include "BaseObject.h"

#define LASER_WIDTH 35
#define LASER_HEIGHT 5
#define SPHERE_WIDTH 10
#define SPHERE_HEIGHT 10


class AmoObject : public BaseObject
{
public:
	enum AmoType
	{
		NONE = 0,
		LASER,
		SPHERE
	};
	AmoObject();
	~AmoObject();

	void HandleInputAction(SDL_Event e);
	void HandleMove(const int& xBorder, const int& yBorder);
	void HandleMoveRightToLeft();

	int get_type() const { return amo_type; }
	void set_type(const int& type) { this->amo_type = type; }

	bool get_IsMove() const { return this->isMove; }
	void set_IsMove(bool isMove) { this->isMove = isMove; }

	void set_xVal(const int& x) { xVal = x; }
	void set_yVal(const int& y) { yVal = y; }
	int get_xVal() const { return xVal; }
	int get_yVal() const { return yVal; }

	void Set_Width_Height(const int& w, const int& h)
	{
		this->rect.w = w;
		this->rect.h = h;
	}

private:
	int xVal;
	int yVal;
	bool isMove;
	int amo_type;
};


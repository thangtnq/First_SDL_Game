#pragma once

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

class MainObject :public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event e, Mix_Chunk* bulletSound[2]);
	void HandleMove();
	void set_AmoList(std::vector<AmoObject*> amoList)
	{
		p_AmoList = amoList;
	}
	std::vector<AmoObject*> get_AmoList() const { return p_AmoList; }

	void makeAmo(SDL_Surface* g_screen);
	void removeAmo(const int& idx);
private:
	int xVal;
	int yVal;

	std::vector<AmoObject*> p_AmoList;
};


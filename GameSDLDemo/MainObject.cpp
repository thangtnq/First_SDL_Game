#include "MainObject.h"

MainObject::MainObject() :
	xVal(0), yVal(0)
{
	rect.x = 0;
	rect.y = 0;
	rect.w = WIDTH_MAIN_OBJECT;
	rect.h = HEIGHT_MAIN_OBJECT;
}

MainObject::~MainObject()
{}

void MainObject::HandleInputAction(SDL_Event e, Mix_Chunk* bulletSound[2])
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			yVal -= HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_DOWN:
			yVal += HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_RIGHT:
			xVal += WIDTH_MAIN_OBJECT / 4;
			break;
		case SDLK_LEFT:
			xVal -= WIDTH_MAIN_OBJECT / 4;
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			yVal += HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_DOWN:
			yVal -= HEIGHT_MAIN_OBJECT / 4;
			break;
		case SDLK_RIGHT:
			xVal -= WIDTH_MAIN_OBJECT / 4;
			break;
		case SDLK_LEFT:
			xVal += WIDTH_MAIN_OBJECT / 4;
			break;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* pAmo = new AmoObject();
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			pAmo->Set_Width_Height(LASER_WIDTH, LASER_HEIGHT);
			pAmo->LoadIMG("Image/laser.png");
			pAmo->set_type(AmoObject::LASER);
			Mix_PlayChannel(-1, bulletSound[0], 0);
		}
		else if (e.button.button == SDL_BUTTON_RIGHT)
		{
			pAmo->Set_Width_Height(SPHERE_WIDTH, SPHERE_HEIGHT);
			pAmo->LoadIMG("Image/sphere.png");
			pAmo->set_type(AmoObject::SPHERE);
			Mix_PlayChannel(-1, bulletSound[1], 0);
		}

		pAmo->SetRect(this->rect.x + this->rect.w - 40, this->rect.y + this->rect.h*4/5);
		pAmo->set_IsMove(true);
		pAmo->set_xVal(20);
		p_AmoList.push_back(pAmo);
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{

	}
	else
	{

	}
}

void MainObject::HandleMove()
{
	this->rect.x += xVal;
	if(this->rect.x < 0 || (this->rect.x + WIDTH_MAIN_OBJECT) > WIDTH)
	{
		rect.x -= xVal;
	}
	this->rect.y += yVal;
	if (this->rect.y < 0 || (this->rect.y + HEIGHT_MAIN_OBJECT) > HEIGHT - 200)
	{
		rect.y -= yVal;
	}
}

void MainObject::makeAmo(SDL_Surface* des)
{
	for (unsigned int i = 0; i < p_AmoList.size(); i++)
	{
		AmoObject* pAmo = p_AmoList.at(i);
		if (pAmo != nullptr)
		{
			if (pAmo->get_IsMove())
			{
				pAmo->Show(des);
				pAmo->HandleMove(WIDTH, HEIGHT);
			}
			else
			{
				if (pAmo != nullptr)
				{
					p_AmoList.erase(p_AmoList.begin() + i);
					delete pAmo;
				}
			}
		}
	}
}

void MainObject::removeAmo(const int& idx)
{
	for (int i = 0; i < p_AmoList.size(); i++)
	{
		if(idx < p_AmoList.size())
		{
			AmoObject* pAmo = p_AmoList.at(idx);
			p_AmoList.erase(p_AmoList.begin() + idx);
			if (pAmo != nullptr)
			{
				delete pAmo;
			}
		}
	}	
}
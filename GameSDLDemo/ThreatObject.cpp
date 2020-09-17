#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	rect.x = WIDTH;
	rect.y = 0.5*HEIGHT;
	rect.w = THREAT_WIDTH;
	rect.h = THREAT_HEIGHT;
	xVal = 0;
	yVal = 0;
}

ThreatObject::~ThreatObject()
{
	if (p_AmoList.size() > 0)
	{
		for (int i = 0; i < p_AmoList.size(); i++)
		{
			AmoObject* pAmo = p_AmoList.at(i);
			if (pAmo != nullptr)
				delete pAmo;
		}
		p_AmoList.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* pAmo)
{
	if (pAmo != nullptr)
	{
		if (pAmo->LoadIMG("Image/sphere.png"))
		{
			pAmo->set_IsMove(true);
			pAmo->Set_Width_Height(SPHERE_WIDTH, SPHERE_HEIGHT);
			pAmo->set_type(AmoObject::SPHERE);
			pAmo->SetRect(rect.x, rect.y + rect.h * 0.5);
			pAmo->set_xVal(8);
			this->p_AmoList.push_back(pAmo);
		}
	}
}

void ThreatObject::makeAmo(SDL_Surface* des, const int& xLimit, const int& yLimit)
{
	for (int i = 0; i < p_AmoList.size(); i++)
	{
		AmoObject* pAmo = p_AmoList.at(i);
		if (pAmo != nullptr)
		{
			if (pAmo->get_IsMove())
			{
				pAmo->Show(des);
				pAmo->HandleMoveRightToLeft();
			}
			else
			{
				pAmo->set_IsMove(true);
				pAmo->SetRect(rect.x, rect.y + rect.h * 0.5);
			}
		}
	}
}

void ThreatObject::HandleMove(const int& xBorder, const int& yBorder)
{
	rect.x -= xVal;
	if (rect.x < 0)
	{
		rect.x = WIDTH;
		int rand_y = rand() % 400;
		if (rand_y > HEIGHT - UNDER_LIMIT_THREAT)
			rand_y = HEIGHT * 0.3;
		rect.y = rand_y;
	}
}

void ThreatObject::HandleInputAction(SDL_Event e)
{

}

void ThreatObject::Reset(const int& xBorder)
{
	rect.x = xBorder;
	int rand_y = rand() % 400;
	if (rand_y > HEIGHT - UNDER_LIMIT_THREAT)
		rand_y = HEIGHT * 0.3;
	rect.y = rand_y;

	for (int i = 0; i < p_AmoList.size(); i++)
	{
		AmoObject* pAmo = p_AmoList.at(i);
		if (pAmo != nullptr)
			ResetAmo(pAmo);
	}
}

void ThreatObject::ResetAmo(AmoObject* pAmo)
{
	pAmo->SetRect(rect.x, rect.y + rect.h * 0.5);
}
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include <time.h>
#include <stdlib.h>


#undef main


int main(int arc, char* argv[])
{
	bool is_RunScreen = true;
	int bkground_x = 0;
	bool is_Quit = false;
	if (!SDLCommonFunc::Init())
		return 1;

	g_background = SDLCommonFunc::LoadImage("Image/bg600.png");

	if (g_background == nullptr)
		return 1;

	//make main object
	MainObject planeObject;
	if (!planeObject.LoadIMG("Image/plane_fly.png"))
		return 1;
	planeObject.SetRect(100, 200);

	//Init explosion object
	ExplosionObject exp_main;
	if (!exp_main.LoadIMG("Image/exp_main.png"))
		return 1;
	exp_main.setClip();

	//make Threat Object
	ThreatObject* pThreadList = new ThreatObject[NUM_THREAT];

	for (int i = 0; i < NUM_THREAT; i++)
	{
		ThreatObject* pThreat = pThreadList + i;
		if (pThreat)
		{
			if (!pThreat->LoadIMG("Image/af1.png"))
				return 1;

			srand(time(NULL));
			int rand_y = rand() % 400;
			if (rand_y > HEIGHT - 200)
				rand_y = HEIGHT * 3/10;


			pThreat->SetRect(WIDTH + i * 400, rand_y);
			pThreat->set_xVal(3);

			AmoObject* pAmoObject = new AmoObject();
			pThreat->InitAmo(pAmoObject);
		}		
	}

	while (!is_Quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				is_Quit = true;
				break;
			}
			planeObject.HandleInputAction(g_event);
		}

		//Apply background case 1
		bkground_x -= 2;
		SDLCommonFunc::ApplySurface(g_background, g_screen, bkground_x, 0);
		SDLCommonFunc::ApplySurface(g_background, g_screen, bkground_x + WIDTH, 0);

		if (bkground_x <= -WIDTH)
			bkground_x = 0;

		//Apply background case 2
		/*if (is_RunSCreen)
		{
			bkground_x -= 2;
			if (bkground_x <= WIDTH - BG_WIDTH)
				is_RunSCreen = false;
			else
				SDLCommonFunc::ApplySurface(g_background, g_screen, bkground_x, 0);
		}
		else
			SDLCommonFunc::ApplySurface(g_background, g_screen, bkground_x, 0);*/


		//implement main object
		planeObject.HandleMove();
		planeObject.Show(g_screen);		
		planeObject.makeAmo(g_screen);

		//implement threat objects
		ThreatObject* pThreat = nullptr;
		for (int i = 0; i < NUM_THREAT; i++)
		{
			pThreat = pThreadList + i;
			if (pThreat != nullptr)
			{
				pThreat->HandleMove(WIDTH, HEIGHT);
				pThreat->Show(g_screen);				
				pThreat->makeAmo(g_screen, WIDTH, HEIGHT);

				//check collision main and threats
				bool is_Col = SDLCommonFunc::checkCollision(planeObject.GetRect(), pThreat->GetRect());
				if (is_Col)
				{
					for (int ex = 0; ex < 4; ex++)
					{
						int x_pos = planeObject.GetRect().x + planeObject.GetRect().w * 0.5 - EXP_WIDTH * 0.5;
						int y_pos = planeObject.GetRect().y + planeObject.GetRect().h * 0.5 - EXP_HEIGHT * 0.5;

						exp_main.setFrame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.showEx(g_screen);
						SDL_Delay(100);

						if (SDL_Flip(g_screen) == -1)
							return 1;
					}

					if (MessageBox(NULL, L"Game Over!!!!", L"Info", MB_OK) == IDOK)
					{
						delete[] pThreadList;
						SDLCommonFunc::CleanUp();
						SDL_Quit();
						return 1;
					}
				}	

				std::vector<AmoObject*> threatAmo = pThreat->get_AmoList();
				for (int ta = 0; ta < threatAmo.size(); ta++)
				{
					AmoObject* tAmo = threatAmo.at(ta);
					if (tAmo != nullptr)
					{
						bool tAmo_Col = SDLCommonFunc::checkCollision(tAmo->GetRect(), planeObject.GetRect());
						if (tAmo_Col)
						{
							if (MessageBox(NULL, L"Game Over!!!!", L"Info", MB_OK) == IDOK)
							{
								delete[] pThreadList;
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return 1;
							}
						}
					}
				}

				std::vector<AmoObject*> amo_List = planeObject.get_AmoList();
				for (int im = 0; im < amo_List.size(); im++)
				{
					AmoObject* pAmo = amo_List.at(im);
					if (pAmo != nullptr)
					{
						bool ret_Col = SDLCommonFunc::checkCollision(pAmo->GetRect(), pThreat->GetRect());
						if (ret_Col)
						{
							planeObject.removeAmo(im);
							pThreat->Reset(WIDTH + i * 400);
						}
					}
				}

				
			}
		}

		//update screen
		if (SDL_Flip(g_screen) == -1)
			return 1;
	}

	delete[] pThreadList;
	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 0;
}
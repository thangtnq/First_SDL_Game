#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include <time.h>
#include <stdlib.h>


#undef main


bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	g_screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
	if (g_screen == nullptr)
		return false;
	return true;
}


int main(int arc, char* argv[])
{
	bool is_Quit = false;
	if (!Init())
		return 1;

	g_background = SDLCommonFunc::LoadImage("Image/bk1.png");

	if (g_background == nullptr)
		return 1;

	//make main object
	MainObject humanObject;
	if (!humanObject.LoadIMG("Image/plane_fly.png"))
		return 1;
	humanObject.SetRect(100, 200);

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
			humanObject.HandleInputAction(g_event);
		}

		//Apply background
		SDLCommonFunc::ApplySurface(g_background, g_screen, 0, 0);

		//implement main object
		humanObject.Show(g_screen);
		humanObject.HandleMove();
		humanObject.makeAmo(g_screen);

		//implement threat objects
		ThreatObject* pThreat = nullptr;
		for (int i = 0; i < NUM_THREAT; i++)
		{
			pThreat = pThreadList + i;
			if (pThreat != nullptr)
			{
				pThreat->Show(g_screen);
				pThreat->HandleMove(WIDTH, HEIGHT);
				pThreat->makeAmo(g_screen, WIDTH, HEIGHT);
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
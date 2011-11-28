/*
 * Main.cpp
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#include "Main.h"

Main::Main()
{
	Running = true;
	pDisplay = NULL;
	pBackground = NULL;

	Difficulty = 1;
	m_fTime = 0.0f;
}

bool Main::OnInit(CL_ParamList* pCL_Params)
{
	Uint16 DisplayW, DisplayH;
	DisplayW = CheckCL_Param(pCL_Params,"Width").intvalue;
	DisplayH = CheckCL_Param(pCL_Params,"Height").intvalue;
	Difficulty = CheckCL_Param(pCL_Params,"Difficulty").intvalue;

	srand(time(NULL));

	if(!DisplayW) DisplayW = 512;
	if(!DisplayH) DisplayH = 240;
	if(!Difficulty) Difficulty = 1;

	if(SDL_Init(SDL_INIT_VIDEO))
		return false;

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, 100);

	if((pDisplay = SDL_SetVideoMode(DisplayW, DisplayH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
		return false;

	if((pBackground = CSurface::Load("Background.png")) == NULL)
		return false;

	if(!Pig.OnInit(40, 168, 55, 20, 2, 20, 5, "PigSprite.png"))
		return false;

	if(!GameOver.OnInit())
		return false;

	return true;
}

void Main::OnExit()
{
	CExplosion::ExitAll();

	CRocket::ExitAll();

	Pig.OnExit();

	GameOver.OnExit();

	SDL_FreeSurface(pDisplay);

	SDL_Quit();
}

void Main::OnEvent(SDL_Event* pEvent)
{
	Pig.OnEvent(pEvent);
}

void Main::OnMove(float fTime)
{
	if(Pig.GetLife() < 0)
		return;

	CExplosion::MoveAll(fTime);
	for(Uint32 i=0;i<CExplosion::ExplosionList.size();i++)
		if(CExplosion::ExplosionList[i])
			if(CExplosion::ExplosionList[i]->GetTimeRemaining() < 0)
				CExplosion::RemoveExplosion(CExplosion::ExplosionList[i]);

	Pig.OnMove(fTime);
	CRocket::MoveAll(fTime);

	eCollisionReturn Collision = NONE;
	for(Uint32 i=0;i<CRocket::RocketList.size();i++)
		if(CRocket::RocketList[i])
			if((Collision = CRocket::RocketList[i]->CheckCollision(&Pig)) != NONE)
			{
				if(Collision == PIG) Pig.LoseLife();

				CExplosion::InitExplosion(CRocket::RocketList[i]->GetX()+7,CRocket::RocketList[i]->GetY()-7,rand() % 5 + 2);
				CRocket::RemoveRocket(CRocket::RocketList[i]);
			}

	m_fTime += fTime;
	if(m_fTime > 1.25f / Difficulty)
	{
		CRocket::Spawn(Pig.GetX() -0.25f * Pig.GetV(), Pig.GetX() + 2.0f * Pig.GetV(), -96, -48, 15 + Pig.GetV() * 0.5f, 15 + Pig.GetV() * 0.75f);
		m_fTime -= 1.25f / Difficulty;
	}
}

void Main::OnRender()
{
	SDL_FillRect(pDisplay, NULL, SDL_MapRGB(pDisplay->format, 0,0,0));

	if(Pig.GetLife() < 0)
		GameOver.Render(pDisplay);
	else
	{
		int Offset = (int)(Pig.GetX() - 40);

		int BackgroundOffset = Offset % pBackground->w;
		CSurface::Blit(pBackground, pDisplay, -pBackground->w - BackgroundOffset, 0);
		CSurface::Blit(pBackground, pDisplay, -BackgroundOffset, 0);
		CSurface::Blit(pBackground, pDisplay, pBackground->w - BackgroundOffset, 0);

		Pig.OnRender(pDisplay, Pig.GetX() - Offset, Pig.GetY());

		CRocket::RenderAll(pDisplay, Offset);

		CExplosion::RenderAll(pDisplay, Offset);
	}

	SDL_Flip(pDisplay);
}

int Main::OnExecute(CL_ParamList* pCL_Params)
{
	if(!OnInit(pCL_Params))
		return -1;

	SDL_Event Event;

	Uint32 t1,t2;
	float fTime = 0.0f;

	while(Running)
	{
		t1 = SDL_GetTicks();
		while(SDL_PollEvent(&Event))
		{
			if(Event.type == SDL_QUIT)
				Running = false;
			else OnEvent(&Event);
		}
		OnMove(fTime);
		OnRender();
		t2 = SDL_GetTicks();
		fTime = (float)(t2-t1)/1000.0f;
	}

	OnExit();
	return 1;
}

int main(int argc, char** argv)
{
	CL_ParamList CL_Params = ParseCommandLine(argc, argv);
	Main App;
	int ret = App.OnExecute(&CL_Params);
	DeleteCL_Params(CL_Params.Head);
	return ret;
}

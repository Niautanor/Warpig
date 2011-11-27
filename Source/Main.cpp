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
}

bool Main::OnInit(CL_ParamList* pCL_Params)
{
	Uint16 DisplayW, DisplayH;
	DisplayW = CheckCL_Param(pCL_Params,"Width").intvalue;
	DisplayH = CheckCL_Param(pCL_Params,"Height").intvalue;

	if(!DisplayW) DisplayW = 512;
	if(!DisplayH) DisplayH = 240;

	if(SDL_Init(SDL_INIT_VIDEO))
		return false;

	if((pDisplay = SDL_SetVideoMode(DisplayW, DisplayH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
		return false;

	if((pBackground = CSurface::Load("Background.png")) == NULL)
		return false;

	if(!Pig.OnInit(40, 168, 55, 20, 2, 20, "PigSprite.png"))
		return false;

	CRocket* R = new CRocket;
	if(!R->OnInit(300,-30,50))
		return false;
	CRocket::AddRocket(R);
	R = new CRocket;
	if(!R->OnInit(500, -70, 80))
		return false;
	CRocket::AddRocket(R);

	return true;
}

void Main::OnExit()
{
	CRocket::ExitAll();

	Pig.OnExit();

	SDL_FreeSurface(pDisplay);

	SDL_Quit();
}

void Main::OnEvent(SDL_Event* pEvent)
{
	Pig.OnEvent(pEvent);
}

void Main::OnMove(float fTime)
{
	Pig.OnMove(fTime);
	CRocket::MoveAll(fTime);

	for(Uint32 i=0;i<CRocket::RocketList.size();i++)
		if(CRocket::RocketList[i])
			if(CRocket::RocketList[i]->CheckCollision(&Pig))
				CRocket::RemoveRocket(CRocket::RocketList[i]);
}

void Main::OnRender()
{
	SDL_FillRect(pDisplay, NULL, SDL_MapRGB(pDisplay->format, 0,0,0));

	int Offset = (int)(Pig.GetX() - 40);

	int BackgroundOffset = Offset % pBackground->w;
	CSurface::Blit(pBackground, pDisplay, -pBackground->w - BackgroundOffset, 0);
	CSurface::Blit(pBackground, pDisplay, -BackgroundOffset, 0);
	CSurface::Blit(pBackground, pDisplay, pBackground->w - BackgroundOffset, 0);

	Pig.OnRender(pDisplay, Pig.GetX() - Offset, Pig.GetY());

	CRocket::RenderAll(pDisplay, Offset);

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

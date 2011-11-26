/*
 * Main.cpp
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#include <iostream>

#include "CommandLine.h"

#include "Main.h"

Main::Main()
{
	Running = true;
	pDisplay = NULL;
}

bool Main::OnInit(CL_ParamList* pCL_Params)
{
	Uint16 DisplayW, DisplayH;
	DisplayW = CheckCL_Param(pCL_Params,"Width").intvalue;
	DisplayH = CheckCL_Param(pCL_Params,"Height").intvalue;

	if(!DisplayW) DisplayW = 1280;
	if(!DisplayH) DisplayH = 720;

	if(SDL_Init(SDL_INIT_VIDEO))
		return false;

	if((pDisplay = SDL_SetVideoMode(DisplayW, DisplayH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
		return false;

	return true;
}

void Main::OnExit()
{
	SDL_FreeSurface(pDisplay);

	SDL_Quit();
}

void Main::OnEvent(SDL_Event* pEvent)
{

}

void Main::OnMove(float fTime)
{

}

void Main::OnRender()
{
	SDL_FillRect(pDisplay, NULL, SDL_MapRGB(pDisplay->format, 0,0,0));

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

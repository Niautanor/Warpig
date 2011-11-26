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

	while(Running)
	{
		while(SDL_PollEvent(&Event))
		{
			if(Event.type == SDL_QUIT)
				Running = false;
		}
		OnRender();
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

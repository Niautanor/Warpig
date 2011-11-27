/*
 * Main.h
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#pragma once/* MAIN_H_ */

#include "CommandLine.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "CSurface.h"

#include "Entitys/Pig.h"

class Main
{
private:
	bool Running;

	SDL_Surface* pDisplay;
	SDL_Surface* pBackground;

	CPig Pig;

public:
	Main();

	bool OnInit(CL_ParamList* pCL_Params);
	void OnExit();

	int OnExecute(CL_ParamList* pCL_Params);

	void OnEvent(SDL_Event* pEvent);
	void OnMove(float fTime);
	void OnRender();
};

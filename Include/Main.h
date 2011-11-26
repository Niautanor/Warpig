/*
 * Main.h
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#pragma once/* MAIN_H_ */

#include "CommandLine.h"

#include <SDL/SDL.h>

class Main
{
private:
	bool Running;

	SDL_Surface* pDisplay;

public:
	Main();

	bool OnInit(CL_ParamList* pCL_Params);
	void OnExit();

	int OnExecute(CL_ParamList* pCL_Params);

	void OnRender();
};

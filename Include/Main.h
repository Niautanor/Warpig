/*
 * Main.h
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#pragma once/* MAIN_H_ */

#include <time.h>
#include <cstring>
#include <math.h>

#include "CommandLine.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "CSurface.h"

#include "Entities/Pig.h"
#include "Entities/Rocket.h"
#include "Entities/Explosion.h"
#include "Entities/GameOver.h"

class Main
{
private:
	bool Running;

	SDL_Surface* pDisplay;
	SDL_Surface* pBackground;

	CPig Pig;

	float m_fTime;
	Uint8 Difficulty;

	CGameOver GameOver;

	TTF_Font* pFont;

public:
	Main();

	bool OnInit(CL_ParamList* pCL_Params);
	void OnExit();

	int OnExecute(CL_ParamList* pCL_Params);

	void OnEvent(SDL_Event* pEvent);
	void OnMove(float fTime);
	void OnRender();
};

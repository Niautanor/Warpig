/*
 * Intro.h
 *
 *  Created on: 30.11.2011
 *      Author: Tim
 */

#pragma once/* INTRO_H_ */

#include <SDL/SDL.h>

#include "CSurface.h"

class CIntro
{
private:
	SDL_Surface* pIntroImage;

	bool Enabled;
public:
	CIntro();

	bool GetEnabled() { return Enabled; }

	bool OnInit();
	void OnExit();

	void Render(SDL_Surface* pDisplay);
	void OnEvent(SDL_Event* pEvent);
};

/*
 * Intro.cpp
 *
 *  Created on: 30.11.2011
 *      Author: Tim
 */

#include "Entities/Intro.h"

CIntro::CIntro()
{
	pIntroImage = NULL;
	Enabled = true;
}

bool CIntro::OnInit()
{
	if((pIntroImage = CSurface::Load("Intro.png")) == NULL)
		return false;
	return true;
}

void CIntro::OnExit()
{
	SDL_FreeSurface(pIntroImage);
	pIntroImage = NULL;
}

void CIntro::Render(SDL_Surface* pDisplay)
{
	CSurface::Blit(pIntroImage, pDisplay, 0, 0);
}

void CIntro::OnEvent(SDL_Event* pEvent)
{
	if(pEvent->type == SDL_KEYDOWN)
		Enabled = false;
}

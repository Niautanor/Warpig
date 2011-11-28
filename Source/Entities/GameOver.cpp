/*
 * GameOver.cpp
 *
 *  Created on: 28.11.2011
 *      Author: Tim
 */

#include "Entities/GameOver.h"

CGameOver::CGameOver()
{
	pGameOverImage = NULL;
}

bool CGameOver::OnInit()
{
	if((pGameOverImage = CSurface::Load("GameOver.png")) == NULL)
		return false;
	return true;
}

void CGameOver::OnExit()
{
	SDL_FreeSurface(pGameOverImage);
	pGameOverImage = NULL;
}

void CGameOver::Render(SDL_Surface* pDisplay)
{
	CSurface::Blit(pGameOverImage, pDisplay, 0, 0);
}

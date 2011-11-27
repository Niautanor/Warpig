/*
 * CRocket.cpp
 *
 *  Created on: 27.11.2011
 *      Author: Tim
 */

#include "Entities/Rocket.h"

std::vector<CRocket*> CRocket::RocketList;
SDL_Surface* CRocket::pRocketSprite = NULL;

CRocket::CRocket()
{
	X = Y = 0;
	V = 0;
}

bool CRocket::OnInit(float StartX, float StartY, float Velocity)
{
	if(!pRocketSprite)//init pRocketSprite
	{
		if((pRocketSprite = CSurface::Load("RocketSprite.png")) == NULL)
			return false;
	}

	X = StartX;
	Y = StartY;
	V = Velocity;
	return true;
}

void CRocket::OnExit()
{
	if(RocketList.empty())
	{
		SDL_FreeSurface(pRocketSprite);
		pRocketSprite = NULL;
	}
}

eCollisionReturn CRocket::CheckCollision(CPig* pPig)
{
	if((Y + 48) > pPig->GetY() && ((X + 48) > pPig->GetX() || X < (pPig->GetX() - 50)))
		return PIG;
	if((Y + 48) > 208)
		return GROUND;
	return NONE;
}

void CRocket::OnMove(float fTime)
{
	X += V * fTime;
	Y += V * fTime;
}

void CRocket::OnRender(SDL_Surface* pDisplay, float X, float Y)
{
	if(!pRocketSprite)
		return;
	CSurface::Blit(pRocketSprite, pDisplay, X, Y);
}

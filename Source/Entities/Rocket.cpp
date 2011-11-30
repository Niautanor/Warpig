/*
 * CRocket.cpp
 *
 *  Created on: 27.11.2011
 *      Author: Tim
 */

#include "Entities/Rocket.h"

std::vector<CRocket*> CRocket::RocketList;
SDL_Surface* CRocket::pRocketSprite = NULL;

int CRocket::GetRocketId(CRocket* pRocket)
{
	for(Uint32 i=0;i<RocketList.size();i++)
	{
		if(RocketList[i] == pRocket)
			return i;
	}
	return -1;
}

int CRocket::GetNumRockets()
{
	int ret = 0;
	for(Uint32 i=0;i<RocketList.size();i++)
		if(RocketList[i])
			ret++;
	return ret;
}

void CRocket::AddRocket(CRocket* pRocket)
{
	for(Uint32 i=0;i<RocketList.size();i++)
	{
		if(!RocketList[i])
		{
			RocketList[i] = pRocket;
			return;
		}
	}
	RocketList.push_back(pRocket);
}

void CRocket::RemoveRocket(CRocket* pRocket)
{
	int Id = GetRocketId(pRocket);
	if(Id == -1)
		return;
	RocketList[Id]->OnExit();
	delete RocketList[Id];
	RocketList[Id] = NULL;
	if(GetNumRockets() == 0)
	{
		SDL_FreeSurface(pRocketSprite);
		pRocketSprite = NULL;
	}
}

bool CRocket::Spawn(int MinX, int MaxX, int MinY, int MaxY, int MinV, int MaxV)
{
	CRocket* R = new CRocket;
	if(!R->OnInit(rand() % (MaxX-MinX) + MinX, rand() % (MaxY-MinY) + MaxY, rand() % (MaxV-MinV) + MinV))
		return false;
	AddRocket(R);
	return true;
}

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
}

void CRocket::ExitAll()
{
	for(Uint32 i=0;i<RocketList.size();i++)
		if(RocketList[i])
			RemoveRocket(RocketList[i]);
}

eCollisionReturn CRocket::CheckCollision(CPig* pPig)
{
	if((Y + 40) > pPig->GetY() && (X+48) > pPig->GetX() && X < (pPig->GetX() + 50))
		return PIG;
	if((Y + 44) > 208)
		return GROUND;
	return NONE;
}

void CRocket::OnMove(float fTime)
{
	X += V * fTime;
	Y += V * fTime;
}

void CRocket::MoveAll(float fTime)
{
	for(Uint32 i=0;i<RocketList.size();i++)
		if(RocketList[i])
			RocketList[i]->OnMove(fTime);
}

void CRocket::OnRender(SDL_Surface* pDisplay, float X, float Y)
{
	if(!pRocketSprite)
		return;
	CSurface::Blit(pRocketSprite, pDisplay, X, Y);
}

void CRocket::RenderAll(SDL_Surface* pDisplay, int X_Offset)
{
	for(Uint32 i=0;i<RocketList.size();i++)
		if(RocketList[i])
			RocketList[i]->OnRender(pDisplay, RocketList[i]->GetX() - X_Offset, RocketList[i]->GetY());
}

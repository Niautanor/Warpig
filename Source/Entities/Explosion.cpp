/*
 * Explosion.cpp
 *
 *  Created on: 27.11.2011
 *      Author: Tim
 */

#include "Entities/Explosion.h"

SDL_Surface* CExplosion::pExplosionSprite;
std::vector<CExplosion*> CExplosion::ExplosionList;

Uint32 CExplosion::GetExplosionCount()
{
	Uint32 ret = 0;
	for(Uint32 i=0;i<ExplosionList.size();i++)
		if(ExplosionList[i])
			ret++;
	return ret;
}

int CExplosion::GetExplosionId(CExplosion* pExplosion)
{
	for(Uint32 i=0;i<ExplosionList.size();i++)
		if(ExplosionList[i] == pExplosion)
			return i;
	return -1;
}

void CExplosion::AddExplosion(CExplosion* pExplosion)
{
	for(Uint32 i=0;i<ExplosionList.size();i++)
	{
		if(!ExplosionList[i])
		{
			ExplosionList[i] = pExplosion;
			return;
		}
	}
	ExplosionList.push_back(pExplosion);
}

void CExplosion::RemoveExplosion(CExplosion* pExplosion)
{
	int Id = GetExplosionId(pExplosion);
	if(Id == -1)
		return;
	ExplosionList[Id]->OnExit();
	delete ExplosionList[Id];
	ExplosionList[Id] = NULL;
	if(GetExplosionCount() == 0)
	{
		SDL_FreeSurface(pExplosionSprite);
		pExplosionSprite = NULL;
	}
}

CExplosion::CExplosion()
{
	X = Y = 0;
	pExplosionSprite = NULL;
	m_fTime_passed = 0;
	MaxTime = 0;
}

bool CExplosion::OnInit(float x, float y, float duration)
{
	if(!pExplosionSprite)
	{
		if((pExplosionSprite = CSurface::Load("ExplosionSprite.png")) == NULL)
			return false;
	}
	X = x;
	Y = y;
	MaxTime = duration;
	return true;
}

bool CExplosion::InitExplosion(float x, float y, float duration)
{
	CExplosion* E = new CExplosion;
	if(!E->OnInit(x,y,duration))
		return false;
	CExplosion::AddExplosion(E);
	return true;
}

void CExplosion::OnExit()
{
}

void CExplosion::ExitAll()
{
	for(Uint32 i=0;i<ExplosionList.size();i++)
		if(ExplosionList[i])
			RemoveExplosion(ExplosionList[i]);
}

void CExplosion::OnMove(float fTime)
{
	m_fTime_passed += fTime;
}

void CExplosion::MoveAll(float fTime)
{
	for(Uint32 i=0;i<ExplosionList.size();i++)
		if(ExplosionList[i])
			ExplosionList[i]->OnMove(fTime);
}

void CExplosion::OnRender(SDL_Surface* pDisplay, float X, float Y)
{
	CSurface::Blit(pExplosionSprite, pDisplay, X, Y);
}

void CExplosion::RenderAll(SDL_Surface* pDisplay, int Offset)
{
	for(Uint32 i=0;i<ExplosionList.size();i++)
		if(ExplosionList[i])
			ExplosionList[i]->OnRender(pDisplay, ExplosionList[i]->GetX() - Offset, ExplosionList[i]->GetY());
}

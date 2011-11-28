/*
 * Explosion.h
 *
 *  Created on: 27.11.2011
 *      Author: Tim
 */

#pragma once/* EXPLOSION_H_ */

#include <vector>

#include <SDL/SDL.h>

#include "CSurface.h"

class CExplosion
{
private:
	float X, Y;

	float m_fTime_passed;
	float MaxTime;

	static SDL_Surface* pExplosionSprite;

public:
	CExplosion();

	static std::vector<CExplosion*> ExplosionList;
	static Uint32 GetExplosionCount();
	static int GetExplosionId(CExplosion* pExplosion);
	static void AddExplosion(CExplosion* pExplosion);
	static void RemoveExplosion(CExplosion* pExplosion);

	static bool InitExplosion(float x, float y, float duration);

	float GetX() { return X; }
	float GetY() { return Y; }
	float GetTimeRemaining() { return MaxTime - m_fTime_passed; }

	bool OnInit(float x, float y, float duration);
	void OnExit();

	static void ExitAll();

	void OnRender(SDL_Surface* pDisplay, float X, float Y);
	void OnMove(float fTime);

	static void RenderAll(SDL_Surface* pDisplay, int Offset);
	static void MoveAll(float fTime);
};

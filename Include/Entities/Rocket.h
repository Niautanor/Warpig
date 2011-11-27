/*
 * CRocket.h
 *
 *  Created on: 27.11.2011
 *      Author: Tim
 */

#pragma once/* CROCKET_H_ */

#include <vector>

#include <math.h>

#include <SDL/SDL.h>

#include "CSurface.h"

#include "Entities/Pig.h"

enum eCollisionReturn
{
	NONE = 0,
	GROUND,
	PIG
};

class CRocket
{
private:
	float X,Y;
	float V;

	static SDL_Surface* pRocketSprite;

public:
	CRocket();

	float GetX() { return X; }
	float GetY() { return Y; }

	static std::vector<CRocket*> RocketList;
	static int GetRocketId(CRocket* pRocket);
	static int GetNumRockets();
	static void AddRocket(CRocket* pRocket);
	static void RemoveRocket(CRocket* pRocket);

	//static void Spawn();

	eCollisionReturn CheckCollision(CPig* pPig);

	bool OnInit(float StartX, float StartY, float Velocity);
	void OnExit();

	static void RenderAll(SDL_Surface* pDisplay, int X_Offset);//kapselung von OnRender()
	static void MoveAll(float fTime);//und OnMove()

	static void ExitAll();//Entfernt alle Elemente von RocketList und gibt pRocketSprite Frei

	void OnRender(SDL_Surface* pDisplay, float X, float Y);
	void OnMove(float fTime);
};

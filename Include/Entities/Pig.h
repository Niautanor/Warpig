/*
 * Pig.h
 *
 *  Created on: 26.11.2011
 *      Author: Tim
 */

#pragma once/* PIG_H_ */

#include <math.h>

#include <SDL/SDL.h>

#include "CSurface.h"

class CPig
{
private:
	float X;

	float Y_Base;
	float Y_Amplitude;
	float Y_MaxAmp;
	bool Y_Dir;

	float X_Speed, Y_Speed;
	float Accelleration;
	float Y_Accl_Factor;

	SDL_Surface* pSprite;

public:
	CPig();

	float GetX() { return X; }
	float GetY() { return Y_Base + Y_Amplitude; }
	float GetV() { return X_Speed; }

	bool OnInit(float Start_X, float Start_Y, float X_Velocity, float Y_Velocity, float MaxYAmp, float Accl, const char* SpriteName);
	void OnExit();

	void OnMove(float fTime);
	void OnEvent(SDL_Event* pEvent);
	void OnRender(SDL_Surface* pDisplay, Sint16 X, Sint16 Y);
};

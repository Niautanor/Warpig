/*
 * Pig.cpp
 *
 *  Created on: 26.11.2011
 *      Author: Tim
 */

#include "Entitys/Pig.h"

CPig::CPig()
{
	X = Y_Base = 0;
	Y_Amplitude = 0;
	Y_MaxAmp = 0;
	X_Speed = 0;
	Y_Speed = 0;
	Accelleration = 0;
	Y_Dir = true;
}

bool CPig::OnInit(float Start_X, float Start_Y, float X_Velocity, float Y_Velocity, float MaxYAmp, float Accl, const char* SpriteName)
{
	X = Start_X;
	Y_Base = Start_Y;
	Y_MaxAmp = MaxYAmp;
	X_Speed = X_Velocity;
	Y_Speed = Y_Velocity;
	Accelleration = Accl;
	Y_Accl_Factor = Y_Speed / X_Speed;

	if((pSprite = CSurface::Load(SpriteName)) == NULL)
		return false;

	return true;
}

void CPig::OnExit()
{
}

void CPig::OnMove(float fTime)
{
	X += X_Speed * fTime;

	if(Y_Dir)
		Y_Amplitude += fabs(Y_Speed) * fTime;
	else
		Y_Amplitude -= fabs(Y_Speed) * fTime;

	if(Y_Amplitude >  Y_MaxAmp)
		Y_Dir = false;
	if(Y_Amplitude < -Y_MaxAmp)
		Y_Dir = true;
}

void CPig::OnEvent(SDL_Event* pEvent)
{
	if(pEvent->type != SDL_KEYDOWN)
		return;
	else
	{
		switch(pEvent->key.keysym.sym)
		{
		case SDLK_a:
			X_Speed -= Accelleration;
			Y_Speed -= Accelleration * Y_Accl_Factor;
			break;
		case SDLK_d:
			X_Speed += Accelleration;
			Y_Speed += Accelleration * Y_Accl_Factor;
			break;
		default:
			break;
		}
	}
}

void CPig::OnRender(SDL_Surface* pDisplay, Sint16 X, Sint16 Y)
{
	CSurface::Blit(pSprite, pDisplay, X, Y);
}
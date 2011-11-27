/*
 * CSurface.cpp
 *
 *  Created on: 26.11.2011
 *      Author: Tim
 */

#include "CSurface.h"

SDL_Surface* CSurface::Load(const char* FileName)
{
	SDL_Surface* pTemp = IMG_Load(FileName);
	if(!pTemp) return NULL;
	SDL_Surface* pRet = SDL_DisplayFormatAlpha(pTemp);
	return pRet;
}

void CSurface::Blit(SDL_Surface* src, SDL_Surface* dst, Sint16 X, Sint16 Y)
{
	if(!src | !dst)
		return;
	SDL_Rect dstRC;
	dstRC.x = X;
	dstRC.y = Y;

	SDL_BlitSurface(src, NULL, dst, &dstRC);
}

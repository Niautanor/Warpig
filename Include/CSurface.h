/*
 * CSurface.h
 *
 *  Created on: 26.11.2011
 *      Author: Tim
 */

#pragma once/* CSURFACE_H_ */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

namespace CSurface
{
	SDL_Surface* Load(const char* FileName);

	void Blit(SDL_Surface* src, SDL_Surface* dst, Sint16 X, Sint16 Y);

	void BlitText(SDL_Surface* dst, const char* Text, TTF_Font* pFont, Sint16 X, Sint16 Y, Uint8 R = 255, Uint8 G = 255, Uint8 B = 255);
}

/*
 * CSurface.h
 *
 *  Created on: 26.11.2011
 *      Author: Tim
 */

#pragma once/* CSURFACE_H_ */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace CSurface
{
	SDL_Surface* Load(const char* FileName);

	void Blit(SDL_Surface* src, SDL_Surface* dst, Sint16 X, Sint16 Y);
}

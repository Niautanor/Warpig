/*
 * GameOver.h
 *
 *  Created on: 28.11.2011
 *      Author: Tim
 */

#pragma once/* GAMEOVER_H_ */

#include <SDL/SDL.h>

#include "CSurface.h"

class CGameOver
{
private:
	SDL_Surface* pGameOverImage;

public:
	CGameOver();

	bool OnInit();
	void OnExit();

	void Render(SDL_Surface* pDisplay);
};

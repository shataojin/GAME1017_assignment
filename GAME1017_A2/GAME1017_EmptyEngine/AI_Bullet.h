
#pragma once
#ifndef _AiBullet_H_
#define _AiBullet_H_

#include <SDL.h>

class AiBullet
{
private:

	double m_dx, m_dy;

public:
	AiBullet(SDL_FRect dst, double dx, double dy);
	void Update();
	void Render();
	SDL_FRect m_dst;
	bool BdeletME = false;
};

#endif
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include <SDL.h>

class Bullet
{
private:
	
	double m_dx, m_dy;

public:
	Bullet(SDL_FRect dst, double dx, double dy);
	void Update();
	void Render();
	SDL_FRect m_dst;
	bool BdeletME = false;
};

#endif
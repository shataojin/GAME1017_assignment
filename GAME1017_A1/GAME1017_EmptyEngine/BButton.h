#pragma once
#ifndef _BButton_H_
#define _BButton_H_

#include <SDL.h>
#include "Bullet.h"

class BButton
{
private:

	SDL_Point m_startPos; // Don't need this actually.
	double m_angle;
	// Firing properties.
	bool m_hasTarget;
	int m_fireCtr;
	static int s_coolDown;
	int m_speed = 3;
public:

	SDL_Rect m_src, m_dst; // Set x and y of m_dst to/from XML.
	BButton(SDL_Rect dst);
	void Update();
	void Render();
	SDL_Point GetPos() const { return { m_dst.x + m_dst.w / 2, m_dst.y + m_dst.h / 2 }; }
};

#endif
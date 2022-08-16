#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "GameObject.h"
#include "SDL.h"
class Background : public SpriteObject
{
private:
	float m_scrollspeed;
	float m_startX;
	float m_endX;
public:
	
	Background(const SDL_Rect& source, const SDL_FRect& destination, float scrollspeed);
	void Update();
	void Render();
};

#endif
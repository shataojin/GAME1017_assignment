#pragma once
#ifndef _BOX_
#define _BOX_
#include "GameObject.h"


//class sprite
//{
//private:
//	SDL_Rect m_dstinationRect;
//	SDL_Color m_color;
//public:
//	sprite(const SDL_Point& position);
//	void Render();
//
//	static const int kwidth = 128;
//	static const int khight = 128;
//
//	friend class Box;
//};
//
//class Box
//{
//private:
//	static const int kscollspeed = 4;
//	SDL_Point m_position;
//	sprite* m_sprite;
//public:
//	Box(const SDL_Point& position, bool hasSprite = false);
//	~Box();
//	void Update();
//	void Render();
//	const SDL_Point GetPosition() { return m_position; }
//};


//class Box : public AnimatedSpriteObject
//{
//public:
//	Box(SDL_Rect s, SDL_FRect d);
//	//~Box();
//	void Update();
//	void Render();
//private:
//	static const int kscollspeed = 4;
//	 float m_position;
//};


class Box : public SpriteObject
{
private:
	static const int kscollspeed =2;
	int m_boxNumber = 10;
	SDL_FRect m_position;
	Box* m_sprite;
public:

	Box(const SDL_Rect& source, const SDL_FRect& destination);
	~Box();
	void Update();
	void Render();
	const SDL_FRect GetPosition() { return m_position; }
};


#endif

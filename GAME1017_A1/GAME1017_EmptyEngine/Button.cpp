#include "Button.h"
#include "States.h"
#include "Enemy.h"
#include "Engine.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "MathManager.h"

Button::Button(SDL_Rect dst) :m_dst(dst), m_src({ 0,0,285,156 }), m_angle(0.0), m_hasTarget(false), m_fireCtr(0)
{
	m_startPos = { dst.x, dst.y };
}

void Button::Update()
{
	SDL_Point tPos = { GetPos().x, GetPos().y };
	
}

void Button::Render()
{
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), TEMA::GetTexture("bt"), &m_src, &m_dst, m_angle, NULL, SDL_FLIP_NONE); // Change to Ex.
}
#include "BButton.h"
#include "States.h"
#include "Enemy.h"
#include "Engine.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "MathManager.h"

BButton::BButton(SDL_Rect dst) :m_dst(dst), m_src({ 0,0,285,156 }), m_angle(0.0), m_hasTarget(false), m_fireCtr(0)
{
	m_startPos = { dst.x, dst.y };
}

void BButton::Update()
{
	SDL_Point tPos = { GetPos().x, GetPos().y };

}

void BButton::Render()
{
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), TEMA::GetTexture("bb"), &m_src, &m_dst, m_angle, NULL, SDL_FLIP_NONE); // Change to Ex.
}
#include "Turret.h"
#include "States.h"
#include "Enemy.h"
#include "Engine.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "MathManager.h"

int Turret::s_coolDown = 120;

Turret::Turret(SDL_Rect dst) :m_dst(dst), m_src({ 0,0,100,100 }), m_angle(0.0), m_hasTarget(false), m_fireCtr(0)
{
	m_startPos = { dst.x, dst.y };
}

void Turret::Update()
{
	SDL_Point tPos = { GetPos().x, GetPos().y };
	// Click and drag functionality.
	/*if (EVMA::MouseHeld(1) && SDL_PointInRect(&EVMA::GetMousePos(), &m_dst))
	{
		m_dst.x = EVMA::GetMousePos().x - m_dst.w / 2;
		m_dst.y = EVMA::GetMousePos().y - m_dst.h / 2;
	}*/

	if (EVMA::MousePressed(1))
	{
		GameState::Bullets().push_back(new Bullet({ (float)(tPos.x - 2), (float)(tPos.y + 2), (float)4, (float)4 }, 5, 0));
	}


	if (EVMA::KeyHeld(SDL_SCANCODE_W) && m_dst.y > 0)
	{

		m_dst.y -= m_speed;
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_S) && m_dst.y < HEIGHT)
	{

		m_dst.y += m_speed;
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_A) && m_dst.x > 0)
	{

		m_dst.x -= m_speed;
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_D) && m_dst.x < WIDTH * 0.5)
	{

		m_dst.x += m_speed;
	}
}

void Turret::Render()
{
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), TEMA::GetTexture("turret"), &m_src, &m_dst, m_angle, NULL, SDL_FLIP_NONE); // Change to Ex.
}
#include "Bullet.h"
#include "Engine.h"

Bullet::Bullet(SDL_FRect dst, double dx, double dy):m_dst(dst), m_dx(dx), m_dy(dy) { }

void Bullet::Update()
{
	m_dst.x += m_dx;
	m_dst.y += m_dy;

	if (m_dst.x > WIDTH || m_dst.x <0 || m_dst.y >WIDTH || m_dst.y < 0)
	{
		BdeletME = true;
	}
}

void Bullet::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 240, 255, 0, 255);
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_dst);
}

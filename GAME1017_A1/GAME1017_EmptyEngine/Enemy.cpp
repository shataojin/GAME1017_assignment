#include "Enemy.h"
#include "Engine.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "States.h"

int Enemy::s_coolDown = 120;
Enemy::Enemy(SDL_Rect dst) :m_dst(dst), m_src({ 80,0,40,57 }), m_speed(1), m_fireCtr(0) { }

void Enemy::Update()
{
	m_dst.x -= m_speed;

	//if (m_fireCtr > 0) m_fireCtr--;
	//
	//double dx = 6.0; // 6 is a bullet speed.
	//double dy = 0.0;
	//SDL_Point ePos = { GetPos().x, GetPos().y };
	//GameState::Bullets().push_back(new Bullet({ (float)(ePos.x - 2), (float)(ePos.y + 2), (float)4, (float)4 }, dx, dy));
}

void Enemy::Render()
{
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemy"), &m_src, &m_dst, 180.0, NULL, SDL_FLIP_NONE);
}

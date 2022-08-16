#include"box.h"
#include "Engine.h"
#include "EventManager.h"
#include "TextureManager.h"


//sprite::sprite(const SDL_Point& position)
//	:m_dstinationRect({ position.x,position.y , kwidth , khight})
//	, m_color({ (Uint8)(rand() & 255), (Uint8)(rand() & 255), (Uint8)(rand() & 255),255 })
//{
//
//}
//
//void sprite::Render()
//{
//	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(),
//		m_color.r,
//		m_color.g,
//		m_color.b,
//		m_color.a);
//	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &m_dstinationRect);
//}
//
//Box::Box(const SDL_Point& position, bool hasSprite )
//	:m_position(position)
//	,m_sprite(nullptr)
//{
//	if (hasSprite)
//	{
//		m_sprite = new sprite(m_position);
//	}
//}
//
//Box::~Box()
//{
//	if (m_sprite)
//	{
//		delete m_sprite;
//		m_sprite = nullptr;
//	}
//}
//
//void Box::Update()
//{
//	m_position.x -= kscollspeed;
//	if (m_sprite)
//	{
//		m_sprite->m_dstinationRect.x = m_position.x;
//	}
//}
//
//void Box::Render()
//{
//	if (m_sprite)
//	{
//		m_sprite->Render();
//	}
//
//	SDL_Rect destination = { m_position.x,m_position.y,
//	sprite::kwidth,sprite::khight };
//	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
//	SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &destination);
//}
//


//Box::Box(SDL_Rect s, SDL_FRect d) :AnimatedSpriteObject(s, d)
//{
//	m_position = GetDst()->x;
//	SetAnimation(1, 8, 9);
//}
//
//void Box::Update()
//{
//	m_position = m_position - kscollspeed;
//}
//void Box::Render()
//{
//	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("player"),
//		&m_src, &m_dst, 0.0, NULL, SDL_FLIP_NONE);
//}






Box::Box(const SDL_Rect& source, const SDL_FRect& destination )
	:SpriteObject(source, destination),  m_position(destination), m_sprite(nullptr)
{

}

Box::~Box()
{
	delete m_sprite;
	m_sprite = nullptr;
}
void Box::Update()
{
	GetDst()->x -= kscollspeed;
	

}
void Box::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture("bs"), GetSrc(), GetDst());
}
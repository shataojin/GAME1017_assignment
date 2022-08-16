#include "Background.h"
#include "Engine.h"
#include "TextureManager.h"

Background::Background(const SDL_Rect& source, const SDL_FRect& destination, float scrollspeed)
:SpriteObject(source, destination), m_scrollspeed(scrollspeed)
{
	m_startX = GetDst()->x;
	m_endX = m_startX - GetDst()->w;
}

void Background::Update()
{
	if (GetDst()->x <= m_endX)
	{
		GetDst()->x = m_startX;
	}
	GetDst()->x -= m_scrollspeed;
}
void Background::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture("bg"), GetSrc(), GetDst());
}
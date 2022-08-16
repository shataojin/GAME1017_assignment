#include "Button3.h"
#include "CollisionManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "StateManager.h"
#include "SoundManager.h"
Button3::Button3(SDL_Rect s, SDL_FRect d, const char* k) :SpriteObject(s, d), m_state(STATE_UP), m_key(k) {}

void Button3::Update()
{
	SOMA::Load("Aud/win.wav", "play", SOUND_SFX);
	SOMA::Load("Aud/died.wav", "exit", SOUND_SFX);
	SOMA::Load("Aud/Fire.wav", "raesume", SOUND_SFX);
	bool col = COMA::PointAABBCheck(EVMA::GetMousePos(), m_dst);
	EVMA::SetCursor(col?SDL_SYSTEM_CURSOR_HAND:SDL_SYSTEM_CURSOR_ARROW);
	switch (m_state)
	{
	case STATE_UP:
		if (col) m_state = STATE_OVER;
		break;
	case STATE_OVER:
		if (!col) m_state = STATE_UP;
		else if (col && EVMA::MousePressed(1)) m_state = STATE_DOWN; // 1 is left mouse.
		break;
	case STATE_DOWN:
		if (EVMA::MouseReleased(1)) // Left mouse released.
		{
			if (col)
			{
				m_state = STATE_OVER;
				Execute();
				EVMA::SetCursor(SDL_SYSTEM_CURSOR_ARROW);
			}
			else
				m_state = STATE_UP;
		}
		break;
	}
}

void Button3::Render()
{
	m_src.x = m_src.w * (int)m_state; 
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture(m_key), &m_src, &m_dst);
}

PlayButton::PlayButton(SDL_Rect s, SDL_FRect d, const char* k) :Button3(s, d, k) {}

void PlayButton::Execute()
{
	SOMA::PlaySound("play");
	STMA::ChangeState(new GameState());
	
}

ExitButton::ExitButton(SDL_Rect s, SDL_FRect d, const char* k) :Button3(s, d, k) {}

void ExitButton::Execute()
{
	SOMA::PlaySound("exit");
	STMA::Quit();
}

RaesumeButton::RaesumeButton(SDL_Rect s, SDL_FRect d, const char* k) :Button3(s, d, k) {}

void RaesumeButton::Execute()
{
	SOMA::PlaySound("raesume");
	STMA::PopState();

}






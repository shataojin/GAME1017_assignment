#include "PlatformPlayer.h"
#include "EventManager.h"
#include "TextureManager.h"
#include <cmath>

PlatformPlayer::PlatformPlayer(SDL_Rect s, SDL_FRect d) :AnimatedSpriteObject(s, d),
m_state(STATE_JUMPING), m_isGrounded(false), m_isFacingLeft(false),
m_maxVelX(9.0), m_maxVelY(JUMPFORCE), m_grav(GRAVITY), m_drag(0.85)
{
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	SetAnimation(1, 8, 9);  // Initialize jump animation. 
}

void PlatformPlayer::Update()
{
	switch (m_state) // Inside each case is the behaviour in and transitions from that state.
	{
	case STATE_IDLING:
		// Transition to run.
		if (EVMA::KeyPressed(SDL_SCANCODE_A) || EVMA::KeyPressed(SDL_SCANCODE_D))
		{
			m_state = STATE_RUNNING;
			SetAnimation(3, 0, 8, 256); // , 256
		}
		// Transition to jump.
		else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_isGrounded)
		{
			m_accelY = -JUMPFORCE; // SetAccelY(-JUMPFORCE);
			m_isGrounded = false;
			m_state = STATE_JUMPING;
			SetAnimation(1, 8, 9, 256);
		}
		break;
	case STATE_RUNNING:
		// Move on ground.
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			m_accelX = -1.5;
			// Set accelX to negative.
			if (!m_isFacingLeft)
				m_isFacingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_accelX = 1.5;
			// Set accelX to positive.
			if (m_isFacingLeft)
				m_isFacingLeft = false;
		}
		// Transition to idle.
		if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_state = STATE_IDLING;
			SetAnimation(1, 0, 1, 256); // , 256
			
		}
		// Transition to jump.
		else if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_isGrounded)
		{
			m_accelY = -JUMPFORCE;
			m_isGrounded = false;
			m_state = STATE_JUMPING;
			SetAnimation(1, 8, 9, 256);
		}
		break;
	case STATE_JUMPING:
		// Move in mid-air.
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			m_accelX = -1.5;
			// Set accelX to negative.
			if (!m_isFacingLeft)
				m_isFacingLeft = true;
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_accelX = 1.5;
			// Set accelX to positive.
			if (m_isFacingLeft)
				m_isFacingLeft = false;
		}
		// Transition to run.
		if (m_isGrounded)
		{

			m_state = STATE_RUNNING;
			SetAnimation(3, 0, 8, 256);
		}
		break;

	case STATE_ROLLING:

		if (EVMA::KeyHeld(SDL_SCANCODE_S))
		{
			
		}
	}
	// Player movement. Universal for all states. X-axis first.
	m_velX += m_accelX;
	m_velX *= (m_isGrounded ? m_drag : 1.0); // Cheeky deceleration.
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX);
	m_dst.x += static_cast<float>(m_velX); // May have to cast to (int)

	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), m_maxVelY); // (m_grav * 5.0)
	m_dst.y += static_cast<float>(m_velY);

	m_accelX = m_accelY = 0.0; // Resetting accel every frame.
	// Invoke the animation.
	Animate();
	// Wrap the player on-screen. For you to do.
	
	// Y-axis now.

	// Animate();
}

void PlatformPlayer::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("player"),
		&m_src, &m_dst, 0.0, NULL, SDL_FLIP_NONE);
	// To animate the sprite, use SDL_RenderCopyExF() and you will have to access the TextureManager and pass in a key such as "player".
	// But for this part, we're just going to use a colored square.
	/*SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRectF(Engine::Instance().GetRenderer(), &m_dst);*/
}

void PlatformPlayer::Stop()
{
	StopX();
	StopY();
}

void PlatformPlayer::StopX() { m_velX = 0.0; }

void PlatformPlayer::StopY() { m_velY = 0.0; }

void PlatformPlayer::SetAccelX(double a) { m_accelX = a; }

void PlatformPlayer::SetAccelY(double a) { m_accelY = a; }

void PlatformPlayer::SetX(float x) { m_dst.x = x; }

void PlatformPlayer::SetY(float y) { m_dst.y = y; }

void PlatformPlayer::SetGrounded(bool g) { m_isGrounded = g; }

bool PlatformPlayer::IsGrounded() { return m_isGrounded; }

double PlatformPlayer::GetVelX() { return m_velX; }

double PlatformPlayer::GetVelY() { return m_velY; }
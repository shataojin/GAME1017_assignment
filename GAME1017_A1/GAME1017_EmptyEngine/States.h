#pragma once
#ifndef _STATES_H_
#define _STATES_H_
#include "Turret.h"
#include "Enemy.h"
#include <vector>
#include "Button.h"
#include "BButton.h"
#include "SoundManager.h"
// An abstract class is one that cannot be instantiated. 
// Why? Because they'd be a base class most likely.
class State // This is the abstract base class for all state subclasses.
{
protected: // Private but inherited.
	State() = default; // Or State() {};
	SDL_Texture* m_pBGText;
	SDL_Renderer* m_pRenderer;
public:
	virtual void Enter() = 0; // = 0 means pure virtual. Method MUST be defined in subclass.
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume() {};
};

class TitleState : public State
{
private: // Private properties.
	std::vector<Button*> m_button;
public: // Public methods.
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class PauseState : public State
{
private:
	std::vector<BButton*> m_buttons;
public: // Public methods.
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class GameState : public State
{
private:
	Mix_Music* m_pMusic;
	Mix_Chunk* m_pSound;
	SDL_Texture* m_pBGText;
	SDL_Renderer* m_pRenderer;
	std::vector<Turret*> m_turrets;
	static std::vector<Enemy*> s_enemies;
	static std::vector<Bullet*> s_bullets;
	static std::vector<AiBullet*> s_aibullets;
	int m_spawnCtr;
	void ClearTurrets();
public: // Public methods.
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	static std::vector<Bullet*>& Bullets() { return s_bullets; }
	static std::vector<Enemy*>& Enemies() { return s_enemies; }
	static std::vector<AiBullet*>& AiBullet() { return s_aibullets; }
};

class LoseState : public State
{
private: // Private properties.
	std::vector<Button*> m_button;
public: // Public methods.
	LoseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class WinState : public State
{
private: // Private properties.
	std::vector<Button*> m_button;
public: // Public methods.
	WinState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

#endif
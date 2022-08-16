#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include "TiledLevel.h"
#include "GameObject.h"

class State // This is the abstract base class for all states
{
public:
	virtual void Enter() = 0; // = 0 means pure virtual - must be defined in subclass
	virtual void Update() = 0; 
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume(); 
	virtual ~State() {} // or = default;
	GameObject* GetGo(const std::string& s);
	auto GetIt(const std::string& s);
	int m_BboxNumber = 10;
	int m_BspawnCtr;
	int m_Btimer=1;
	int BcountNumber = 300;
	int m_SboxNumber = 10;
	int m_SspawnCtr;
	int m_Stimer = 1;
	int ScountNumber = 180;
	int dieTimer = 600;
	int  sec = 1;


protected: // Private but inherited
	State() {} // What does this prevent?
	vector<std::pair<std::string, GameObject*>> m_objects;
	vector<std::pair<std::string, GameObject*>> m_objectre;
	vector<std::pair<std::string, GameObject*>> m_vec;
	vector<std::pair<std::string, GameObject*>> m_Sbox;
	vector<std::pair<std::string, GameObject*>> m_Bbox;
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	virtual void deadtimer();
};

class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class LoseState : public State
{

public: 
	LoseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

#endif


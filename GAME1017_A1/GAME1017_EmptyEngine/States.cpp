#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Engine.h"
#include <string>
#include <vector>
#include"SoundManager.h"

using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	cout << "Enter Title State --> " << endl;
	//load music track, add it to map, and  play
	TEMA::Load("Img/b.jpg", "bg");
	TEMA::Load("Img/startButton.png", "bt");
	m_pMusic = Mix_LoadMUS("audio/Bgm_1.mp3");
	Mix_PlayMusic(m_pMusic, -1);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
	Mix_AllocateChannels(16);
}

void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
	{
		
		STMA::ChangeState( new GameState() );
	}
	for (unsigned i = 0; i < m_button.size(); i++)
	{
		SDL_Rect bPos = m_button[i]->m_dst;
		if (EVMA::MousePressed(1) && (COMA::PointAABBCheck(EVMA::GetMousePos(), bPos)))
		{
			STMA::ChangeState(new GameState());
		}
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), TEMA::GetTexture("bg"), 0, 0);
	m_button.push_back(new Button({ WIDTH / 2 - 75 ,HEIGHT / 2 + 100,150,50 }));
	for (unsigned i = 0; i < m_button.size(); i++)
		m_button[i]->Render();

	State::Render();
}

void TitleState::Exit()
{
	TEMA::Unload("bg");
	TEMA::Unload("bt");
	cout << "exit title state----->" << endl;
}

PauseState::PauseState(){}

void PauseState::Enter()
{
	cout << "Enter pause State --> " << endl;
	TEMA::Load("Img/backButton.png", "bb");
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();
	for (unsigned i = 0; i < m_button.size(); i++)
	{
		SDL_Rect bPos = m_button[i]->m_dst;
		if (EVMA::MousePressed(1) && (COMA::PointAABBCheck(EVMA::GetMousePos(), bPos)))
		{
			STMA::PopState();
		}
	}
}

void PauseState::Render()
{
	// First render the GameState.
	STMA::GetStates().front()->Render();
	// Now render the rest of PauseState.
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 128);
	SDL_Rect rect = { 255, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	m_button.push_back(new Button({ WIDTH / 2 - 75 ,HEIGHT / 2 + 100,150,50 }));
	for (unsigned i = 0; i < m_button.size(); i++)
		m_button[i]->Render();

	State::Render();
}

void PauseState::Exit()
{
	TEMA::Unload("bb");
	cout << "exit pause state" << endl;
}

void GameState::ClearTurrets()
{
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		delete m_turrets[i];
		m_turrets[i] = nullptr;
	}
	m_turrets.clear();
	m_turrets.shrink_to_fit();
}

GameState::GameState():m_spawnCtr(0) {}

void GameState::Enter()
{
	TEMA::Load("Img/background.png", "bg");
	TEMA::Load("Img/2.png", "turret");
	TEMA::Load("Img/mine.png", "enemy");
	m_pMusic = Mix_LoadMUS("audio/Bgm_2.mp3");
	Mix_PlayMusic(m_pMusic, -1);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
	Mix_AllocateChannels(16);
	s_enemies.push_back(new Enemy({512, 200, 40, 57}));
	m_turrets.push_back(new Turret({ 50 ,250,100,100 }));
	
}

void GameState::Update()
{
	if (EVMA::MousePressed(1))
	{
		m_pSound = Mix_LoadWAV("Hockey Shot 3.mp3");
		Mix_PlayChannel(-1, m_pSound, 0);
	}
	if (killCount >= 3)
	{
		m_pSound = Mix_LoadWAV("audio/win.wav");
		Mix_PlayChannel(-1, m_pSound, 0);
		STMA::ChangeState(new WinState());
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_5))
	{
		m_pSound = Mix_LoadWAV("audio/died.wav");
		Mix_PlayChannel(-1, m_pSound, 0);
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_6))
	{
		m_pMusic = Mix_LoadMUS("audio/Bgm_2.mp3");
		Mix_PlayMusic(m_pMusic, -1);
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
		Mix_AllocateChannels(16);
	}

	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState());
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_L))
	{
		STMA::ChangeState(new LoseState());
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_O))
	{
		STMA::ChangeState(new WinState());
	}
	/*if (EVMA::KeyPressed(SDL_SCANCODE_T))
	{
		m_turrets.push_back(new Turret({ 50,250,100,100 }));
	}*/
	if (EVMA::KeyPressed(SDL_SCANCODE_C))
	{
		ClearTurrets();
	}
	if (m_spawnCtr++ % 180 == 0)
		s_enemies.push_back(new Enemy({ 1024 ,rand() % (750-20), 40, 57 }));
	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Update();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Update();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Update();
	for (unsigned i = 0; i < s_aibullets.size(); i++)
		s_aibullets[i]->Update();



	//AI
	//with wall
	//for (unsigned i = 0; i < s_enemies.size(); i++)
	//{
	//	
	//	if (s_enemies[i]->GetPos().x <-20 )
	//	{
	//		cout << "Enemy delete by wall"<<s_enemies[i]->GetPos().y << endl;
	//		delete s_enemies[i];
	//		s_enemies[i]=(new Enemy({ 1024 ,rand() % (720 - 40), 40, 57 }));
	//	}
	//}

	////ai with player
	//for (unsigned i = 0; i < m_turrets.size(); i++)
	//{
	//	SDL_Rect tPos = m_turrets[i]->m_dst;
	//	for (unsigned i = 0; i < s_enemies.size(); i++)
	//	{
	//		SDL_Rect ePos = s_enemies[i]->m_dst;
	//		if (COMA::AABBCheck(ePos, tPos))
	//		{
	//			cout << "change state to lose" << endl;
	//			m_pSound = Mix_LoadWAV("audio/Button.wav");
	//			Mix_PlayChannel(-1, m_pSound, 0);
	//			STMA::ChangeState(new LoseState());
	//			break;
	//		}
	//		
	//	}
	//}


	//// ai bullet with wall

	//for (unsigned i = 0; i < s_aibullets.size(); i++)
	//{
	//	if (s_aibullets[i]->m_dst.x < 0)
	//	{
	//		cout << "ai bullet delete by wall" << s_aibullets[i]->m_dst.x << endl;
	//		delete s_aibullets[i];
	//		s_aibullets[i] = nullptr;
	//		s_aibullets.erase(s_aibullets.begin() + i);
	//		s_aibullets.shrink_to_fit();
	//		break;
	//	}
	//}

	//// ai bullet with player

	//for (unsigned i = 0; i < m_turrets.size(); i++)
	//{
	//	SDL_Rect tPos = m_turrets[i]->m_dst;
	//	for (unsigned i = 0; i < s_aibullets.size(); i++)
	//	{
	//		SDL_FRect bPos = s_aibullets[i]->m_dst;
	//		if (COMA::AABBCheck(tPos, bPos))
	//		{
	//			cout << "change state to lose" << endl;
	//			m_pSound = Mix_LoadWAV("audio/Button.wav");
	//			Mix_PlayChannel(-1, m_pSound, 0);
	//			/*delete s_aibullets[i];
	//			s_aibullets[i] = nullptr;
	//			s_aibullets.erase(s_aibullets.begin() + i);
	//			s_aibullets.shrink_to_fit();

	//			m_turrets.clear();
	//			m_turrets.shrink_to_fit();
	//			s_bullets.clear();
	//			s_bullets.shrink_to_fit();
	//			STMA::ChangeState(new LoseState());*/
	//			break;
	//		}
	//	}
	//}

	// 






	////PLAYER
	////player bullet with wall

	//for (unsigned i = 0; i < m_turrets.size(); i++)
	//{
	//	SDL_Point tPos = { m_turrets[i]->GetPos().x, m_turrets[i]->GetPos().y };
	//	for (unsigned i = 0; i < s_bullets.size(); i++)
	//	{
	//		if (s_bullets[i]->m_dst.x > WIDTH)
	//		{
	//			cout << "player bullet delete by wall" << s_bullets[i]->m_dst.x << endl;
	//			delete s_bullets[i];
	//			s_bullets[i] = nullptr;
	//			s_bullets.erase(s_bullets.begin() + i);
	//			s_bullets.shrink_to_fit();
	//			break;
	//		}
	//	}
	//}

	////player bullet with enemy
	//for (int e = 0; e < s_enemies.size(); e++)
	//{
	//	SDL_Rect ePos = s_enemies[e]->m_dst;
	//	for (int b= 0; b < s_bullets.size(); b++)
	//	{
	//		SDL_FRect bPos = s_bullets[b]->m_dst;
	//		if(COMA::AABBCheck(ePos, bPos))
	//		{
	//			cout << "you killed one enemy......" << endl;
	//			delete s_enemies[e];
	//			s_enemies[e] = (new Enemy({ 1024 ,rand() % (750 - 20), 40, 57 }));
	//			delete s_bullets[e];
	//			s_bullets.erase(s_bullets.begin() + e);
	//			s_bullets.shrink_to_fit();
	//			killCount++;
	//			cout << "kill count: "<< killCount << endl;
	//			m_pSound = Mix_LoadWAV("audio/died.wav");
	//			Mix_PlayChannel(-1, m_pSound, 0);
	//			break;
	//			
	//		}
	//	}
	//}



}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), TEMA::GetTexture("bg"), 0, 0);

	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Render();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Render();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Render();
	for (unsigned i = 0; i < s_aibullets.size(); i++)
		s_aibullets[i]->Render();

	
	// This code below prevents SDL_RenderPresent from running twice in one frame.
	if ( dynamic_cast<GameState*>( STMA::GetStates().back() ) ) // If current state is GameState.
		State::Render();
}

void GameState::Exit()
{
	ClearTurrets();
	for (unsigned i = 0; i < s_enemies.size(); i++)
	{
		delete s_enemies[i];
		s_enemies[i] = nullptr;
	}
	s_enemies.clear();
	s_enemies.shrink_to_fit();
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		delete s_bullets[i];
		s_bullets[i] = nullptr;
	}
	s_bullets.clear();
	s_bullets.shrink_to_fit();
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		delete m_turrets[i];
		m_turrets[i] = nullptr;
	}
	for (unsigned i = 0; i < s_aibullets.size(); i++)
	{
		delete s_aibullets[i];
		s_aibullets[i] = nullptr;
	}
	s_aibullets.clear();
	s_aibullets.shrink_to_fit();
	m_turrets.clear();
	m_turrets.shrink_to_fit();
	TEMA::Unload("bg");
}

void GameState::Resume()
{
	
}

// This is how static properties are allocated.
std::vector<Bullet*> GameState::s_bullets;
std::vector<Enemy*> GameState::s_enemies;
std::vector<AiBullet*> GameState::s_aibullets;




LoseState::LoseState() {}

void LoseState::Enter()
{
	cout << "Enter  State --> " << endl;
	//load music track, add it to map, and  play
	TEMA::Load("Img/cloud.png", "bg");
	TEMA::Load("Img/restartButton.png", "bt");
}

void LoseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
	{
		STMA::ChangeState(new GameState());
	}
	for (unsigned i = 0; i < m_button.size(); i++)
	{
		SDL_Rect bPos = m_button[i]->m_dst;
		if (EVMA::MousePressed(1) && (COMA::PointAABBCheck(EVMA::GetMousePos(), bPos)))
		{
			STMA::ChangeState(new GameState());
		}
	}
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), TEMA::GetTexture("bg"), 0, 0);
	m_button.push_back(new Button({ WIDTH / 2 - 75 ,HEIGHT / 2 + 100,150,50 }));
	for (unsigned i = 0; i < m_button.size(); i++)
		m_button[i]->Render();

	State::Render();
}

void LoseState::Exit()
{
	TEMA::Unload("bg");
	TEMA::Unload("bt");
	cout << "exit state----->" << endl;
}



WinState::WinState() {}

void WinState::Enter()
{
	cout << "Enter  State --> " << endl;
	//load music track, add it to map, and  play
	TEMA::Load("Img/w.jpg", "bg");
	TEMA::Load("Img/restartButton.png", "bt");
}

void WinState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
	{
		STMA::ChangeState(new GameState());
	}

	for (unsigned i = 0; i < m_button.size(); i++)
	{
		SDL_Rect bPos = m_button[i]->m_dst;
		if (EVMA::MousePressed(1) && (COMA::PointAABBCheck(EVMA::GetMousePos(), bPos)))
		{
			STMA::ChangeState(new GameState());
		}
	}
}

void WinState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), TEMA::GetTexture("bg"), 0, 0);
	m_button.push_back(new Button({ WIDTH / 2 - 75 ,HEIGHT / 2 + 100,150,50 }));
	for (unsigned i = 0; i < m_button.size(); i++)
		m_button[i]->Render();
	State::Render();
}

void WinState::Exit()
{
	TEMA::Unload("bg");
	TEMA::Unload("bt");
	cout << "exit  state----->" << endl;
}

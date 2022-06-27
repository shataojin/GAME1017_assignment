#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Engine.h"
#include <string>
#include <vector>
#include "tinyxml2.h"
using namespace tinyxml2;
using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	
}

void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
	{
		
		STMA::ChangeState( new GameState() );
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	
}

PauseState::PauseState(){}

void PauseState::Enter()
{
	
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();
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
	State::Render();
}

void PauseState::Exit()
{
	
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
TEMA::Load("Img/Turret.png", "turret");
	TEMA::Load("Img/Enemies.png", "enemy");
	s_enemies.push_back(new Enemy({512, 200, 40, 57}));
	m_turrets.push_back(new Turret({ 50 ,250,100,100 }));
	//// Create the DOM and load the XML file.
	//XMLDocument xmlDoc;
	//xmlDoc.LoadFile("SavedObjects.xml");
	//XMLNode* pRoot = xmlDoc.FirstChildElement("Root");
	//// Iterate through the Turret elements in the file and push_back new Turrets into the m_turrets vector.
	//XMLElement* pElement = pRoot->FirstChildElement("GameObject");
	//while (pElement != nullptr)
	//{
	//	if (strcmp(pElement->Attribute("class"), "enemies") == 0)
	//	{
	//		int x, y;
	//		pElement->QueryIntAttribute("x_position", &x);
	//		pElement->QueryIntAttribute("y_position", &y);
	//		s_enemies.push_back(new Enemy({ x ,y ,40,57 }));
	//		cout << x << y << endl;
	//	}
	//	else if (strcmp(pElement->Attribute("class"), "turret") == 0)
	//	{
	//		int x,y;
	//		pElement->QueryIntAttribute("x_position", &x);
	//		pElement->QueryIntAttribute("y_position", &y);
	//		m_turrets.push_back(new Turret({ x ,y,100,100 }));
	//		cout << x << y << endl;
	//	}
	//	pElement = pElement->NextSiblingElement("GameObject");
	//}
}

void GameState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState());
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
		s_enemies.push_back(new Enemy({ 1048 ,rand() % (750-20), 40, 57 }));
	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Update();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Update();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Update();
	for (unsigned i = 0; i < s_aibullets.size(); i++)
		s_aibullets[i]->Update();


	// Cleanup bullets and enemies that go off screen.

		// for all bullets
			// if bullet goes off screen (four bounds checks)
				// delete s_bullets[i]
				// set s_bullets[i] to nullptr
	
		// for all enemies, similar to above

	// Check for collisions with bullets and enemies.
	
		// for all bullets
			// for all enemies
				// check collision

	////test loacltion
	//for (unsigned i = 0; i < s_enemies.size(); i++)
	//{
	//	cout << "y" << s_enemies[i]->GetPos().y << endl;
	//}

	//for (unsigned i = 0; i < m_turrets.size(); i++)
	//{
	//	cout << "y" << m_turrets[i]->GetPos().y << endl;
	//	cout << "x" << m_turrets[i]->GetPos().x << endl;
	//}



	//AI
	//with wall
	for (unsigned i = 0; i < s_enemies.size(); i++)
	{
		if (s_enemies[i]->GetPos().x <-20 )
		{
			cout << "Enemy delete by wall"<<s_enemies[i]->GetPos().y << endl;
			delete s_enemies[i];
			s_enemies[i]=(new Enemy({ 1048 ,rand() % (750 - 20), 40, 57 }));
		}
	}

	//ai with player
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		SDL_Rect tPos = m_turrets[i]->m_dst;
		for (unsigned i = 0; i < s_enemies.size(); i++)
		{
			SDL_Rect ePos = s_enemies[i]->m_dst;
			if (COMA::AABBCheck(ePos, tPos))
			{
				cout << "change state to lose" << endl;
				/*STMA::ChangeState(new LoseState());*/
				break;
			}
			
		}
	}


	// ai bullet with wall

	for (unsigned i = 0; i < s_aibullets.size(); i++)
	{
		if (s_aibullets[i]->m_dst.x < 0)
		{
			cout << "player bullet delete by wall" << s_aibullets[i]->m_dst.x << endl;
			delete s_aibullets[i];
			s_aibullets[i] = nullptr;
			s_aibullets.erase(s_aibullets.begin() + i);
			s_aibullets.shrink_to_fit();
			break;
		}
	}

	// ai bullet with player

	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		SDL_Rect tPos = m_turrets[i]->m_dst;
		for (unsigned i = 0; i < s_aibullets.size(); i++)
		{
			SDL_FRect bPos = s_aibullets[i]->m_dst;
			if (COMA::AABBCheck(tPos, bPos))
			{
				cout << "change state to lose" << endl;
				/*STMA::ChangeState(new LoseState());*/
				break;
			}
		}
	}

	 






	//PLAYER
	//player bullet with wall

	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		SDL_Point tPos = { m_turrets[i]->GetPos().x, m_turrets[i]->GetPos().y };
		for (unsigned i = 0; i < s_bullets.size(); i++)
		{
			if (s_bullets[i]->m_dst.x > WIDTH)
			{
				cout << "player bullet delete by wall" << s_bullets[i]->m_dst.x << endl;
				delete s_bullets[i];
				s_bullets[i] = nullptr;
				s_bullets.erase(s_bullets.begin() + i);
				s_bullets.shrink_to_fit();
				break;
			}
		}
	}

	//player bullet with enemy
	for (int e = 0; e < s_enemies.size(); e++)
	{
		SDL_Rect ePos = s_enemies[e]->m_dst;
		for (int b= 0; b < s_bullets.size(); b++)
		{
			SDL_FRect bPos = s_bullets[b]->m_dst;
			if(COMA::AABBCheck(ePos, bPos))
			{
				cout << "you killed one enemy......" << endl;
				delete s_enemies[e];
				s_enemies[e] = (new Enemy({ 1048 ,rand() % (750 - 20), 40, 57 }));
				/*delete s_bullets[e];
				s_bullets[e] = nullptr;
				s_bullets.shrink_to_fit();*/
				break;
				
			}
		}
	}



}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

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
	XMLDocument xmlDoc;
	//DeleteChildren
	xmlDoc.DeleteChildren();
	// Create and insert a Root element.
	XMLNode* pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertEndChild(pRoot);

	for (unsigned i = 0; i < m_turrets.size(); i++)
	{

		/*m_turrets[i]->GetPos().x;
		m_turrets[i]->GetPos().y;*/

		XMLElement* pElement = xmlDoc.NewElement("GameObject");
		pElement->SetAttribute("class", "turret");
		pElement->SetAttribute("x_position", m_turrets[i]->GetPos().x);
		pElement->SetAttribute("y_position", m_turrets[i]->GetPos().y);
		pRoot->InsertEndChild(pElement);
		xmlDoc.SaveFile("SavedObjects.xml");
	}

	for (unsigned i = 0; i < s_enemies.size(); i++)
	{

		/*m_turrets[i]->GetPos().x;
		m_turrets[i]->GetPos().y;*/

		XMLElement* pElement = xmlDoc.NewElement("GameObject");
		pElement->SetAttribute("class", "enemies");
		pElement->SetAttribute("x_position", s_enemies[i]->GetPos().x);
		pElement->SetAttribute("y_position", s_enemies[i]->GetPos().y);
		pRoot->InsertEndChild(pElement);
		xmlDoc.SaveFile("SavedObjects.xml");
	}


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
}

void GameState::Resume()
{
	
}

// This is how static properties are allocated.
std::vector<Bullet*> GameState::s_bullets;
std::vector<Enemy*> GameState::s_enemies;
std::vector<AiBullet*> GameState::s_aibullets;
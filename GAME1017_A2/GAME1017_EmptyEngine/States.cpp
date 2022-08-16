#include "States.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Primitives.h"
#include"PlatformPlayer.h"
#include "Button3.h"
#include"Background.h"
#include <iostream>
using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume(){}

GameObject* State::GetGo(const std::string& s)
{ // Using 'std' just to show origin.
	auto it = std::find_if(m_objects.begin(), m_objects.end(), 
		// Lambda expression/function. An in-function function.
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		} 
	); // End of find_if.
	if (it != m_objects.end())
		return it->second;
	else return nullptr;
}

auto State::GetIt(const std::string& s)
{ 
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	return it;
}



///////remember change pics,quit game not working


// Begin TitleState
TitleState::TitleState(){}

void TitleState::Enter()
{
	TEMA::Load("Img/x.jpg", "background");
	m_objects.push_back(pair<string, GameObject*>("background",
		new Image({ 0, 0, 1024, 768 }, { 0, 0, 1024, 768 }, "background")));
	TEMA::Load("Img/button.png", "play");
	m_objects.push_back(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 400, 100 }, { 412, 450, 200, 50 }, "play")));
	TEMA::Load("Img/exit.png", "exit");
	m_objects.push_back(pair<string, GameObject*>("exit",
		new ExitButton({ 0, 0, 400, 100 }, { 412, 550, 200, 50 }, "exit")));

}

void TitleState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;

	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 0, 16, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void TitleState::Exit()
{
	TEMA::Unload("background");
	TEMA::Unload("play");
	TEMA::Unload("exit");
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
}
// End TitleState

// Begin GameState
GameState::GameState(){}

void GameState::Enter() // Used for initialization.
{
	TEMA::Load("Img/BG.png", "bg");
	m_vec.reserve(10);
	// Backgrounds.
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({0,0,1024,768}, {0,0,1024,768}, 1)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 0,0,1024,768 }, { 1024,0,1024,768 }, 1)));
	// Midgrounds.
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,0,256,512 }, { 0,0,256,512 }, 3)));
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,0,256,512 }, { 256,0,256,512 }, 3)));
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,0,256,512 }, { 512,0,256,512 }, 3)));
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,0,256,512 }, { 768,0,256,512 }, 3)));
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,0,256,512 }, { 1024,0,256,512 }, 3)));


	// Foregrounds.
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,512,521,256 }, { 0,512,512,256 }, 4)));
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,512,521,256 }, { 512,512,512,256 }, 4)));
	m_vec.push_back(pair<string, GameObject*>("bg",new Background({ 1024,512,521,256 }, { 1024,512,512,256 }, 4)));
	/*TEMA::Load("Img/Tiles.png", "tiles");
	TEMA::Load("Img/Player.png", "player");
	m_objects.push_back(pair<string, GameObject*>("level", new TiledLevel(
		24, 32, 32, 32, "Dat/Tiledata.txt", "Dat/Level1.txt", "tiles")));
	m_objects.push_back(pair<string, GameObject*>("player", new PlatformPlayer(
		{ 0,0,128,128 }, { 299,480,64,64 })));*/
	
}

void GameState::Update()
{


	for (auto const& i : m_vec)
{
	i.second->Update();
}

	//for (auto const& i : m_objects)
	//{
	//	i.second->Update();
	//	if (STMA::StateChanging()) return;
	//}

	//if (EVMA::KeyPressed(SDL_SCANCODE_P))
	//{
	//	STMA::PushState(new PauseState()); // Add new PauseState
	//}

	////check collision
	//PlatformPlayer* pObj = static_cast<PlatformPlayer*>(GetGo("player"));
	//SDL_FRect* pBound = pObj->GetDst();
	//TiledLevel* pLevel = static_cast<TiledLevel*>(GetGo("level"));

	//for (unsigned int i = 0; i < pLevel->GetObstacles().size(); i++)
	//{
	//	SDL_FRect* pTile = pLevel->GetObstacles()[i]->GetDst();
	//	if (COMA::AABBCheck(*pBound, *pTile))
	//	{
	//		if ((pBound->y + pBound->h) - (float)pObj->GetVelY() <= pTile->y)
	//		{
	//			pObj->StopY();
	//			pObj->SetY(pTile->y - pBound->h);
	//			pObj->SetGrounded(true);
	//		}

	//		else if (pBound->y - (float)pObj->GetVelY() >= pTile->y + pTile->h)
	//		{
	//			pObj->StopY();
	//			pObj->SetY(pTile->y + pBound->h);
	//		}
	//		else if ((pBound->x + pBound->w) - (float)pObj->GetVelX() <= pTile->x)
	//		{
	//			pObj->StopX();
	//			pObj->SetX(pTile->x - pBound->w);
	//		}
	//		else if (pBound->x - (float)pObj->GetVelX() >= pTile->x + pTile->w)
	//		{
	//			pObj->StopX();
	//			pObj->SetX(pTile->x - pBound->w);
	//		}
	//	}
	//}
}

void GameState::Render()
{

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	//for (auto const& i : m_objects)
	//	i.second->Render();
	for (auto const& i : m_vec)
		i.second->Render();
	if ( dynamic_cast<GameState*>(STMA::GetStates().back()) ) 
		State::Render();
}

void GameState::Exit()
{
	TEMA::Unload( "bg");
	for (auto& i : m_vec)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_vec.clear();
	m_vec.shrink_to_fit();

	/*TEMA::Unload( "tiles");
	TEMA::Unload("player");
	for (auto& i : m_objects)
	{
		delete i.second; 
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();*/
}

void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
}
// End GameState



////problem of  quit


// Begin PauseState
PauseState::PauseState() {}

void PauseState::Enter()
{
	
	TEMA::Load("Img/resume.png", "resume");
	m_objectre.push_back(pair<string, GameObject*>("resume",
		new RaesumeButton({ 0, 0, 400, 100 }, { 412, 300, 200, 50 }, "resume")));
	TEMA::Load("Img/exit.png", "exit");
	m_objects.push_back(pair<string, GameObject*>("exit",
		new ExitButton({ 0, 0, 400, 100 }, { 412, 450, 200, 50 }, "exit")));
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
	for (auto const& i : m_objectre)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
		break;
	}
}

void PauseState::Render()
{
	
	// First render the GameState
	STMA::GetStates().front()->Render();
	// Now render rest of PauseState
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 128);
	SDL_Rect rect = { 256, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	for (auto const& i : m_objects)
		i.second->Render();
	for (auto const& i : m_objectre)
		i.second->Render();
	State::Render();
}

void PauseState::Exit()
{
	TEMA::Unload("resume");
	TEMA::Unload("exit");
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
	for (auto& i : m_objectre)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objectre.clear();
	m_objectre.shrink_to_fit();
	
}
// End PauseState


/////change picture and add contion with paly scene


//Begin LoseState
LoseState::LoseState() {}

void LoseState::Enter()
{
	TEMA::Load("Img/x.jpg", "background");
	m_objects.push_back(pair<string, GameObject*>("background",
		new Image({ 0, 0, 1024, 768 }, { 0, 0, 1024, 768 }, "background")));
	TEMA::Load("Img/button.png", "play");
	m_objects.push_back(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 400, 100 }, { 412, 450, 200, 50 }, "play")));
	TEMA::Load("Img/exit.png", "exit");
	m_objects.push_back(pair<string, GameObject*>("exit",
		new ExitButton({ 0, 0, 400, 100 }, { 412, 550, 200, 50 }, "exit")));
}

void LoseState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;

	}
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 0, 16, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void LoseState::Exit()
{
	TEMA::Unload("background");
	TEMA::Unload("play");
	TEMA::Unload("exit");
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();
}

// End LoseState

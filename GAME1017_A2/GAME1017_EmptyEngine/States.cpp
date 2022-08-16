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
#include"Box.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "tinyxml2.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


using namespace tinyxml2;
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

	SOMA::PlayMusic("title", -1, 2000);
	TEMA::Load("Img/x.jpg", "background");
	m_objects.push_back(pair<string, GameObject*>("background",
		new Image({ 0, 0, 1024, 768 }, { 0, 0, 1024, 768 }, "background")));
	TEMA::Load("Img/button.png", "play");
	m_objects.push_back(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 400, 100 }, { 412, 450, 200, 50 }, "play")));
	TEMA::Load("Img/exit.png", "exit");
	m_objects.push_back(pair<string, GameObject*>("exit",
		new ExitButton({ 0, 0, 400, 100 }, { 412, 550, 200, 50 }, "exit")));
	SOMA::Load("Aud/died.wav", "exit", SOUND_SFX);
	SOMA::Load("Aud/Bgm_2.mp3", "gaem", SOUND_MUSIC);
	SOMA::SetSoundVolume(16);
	SOMA::SetMusicVolume(32);
	SOMA::PlayMusic("gaem", -1, 2000);

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
	SOMA::StopMusic();
	SOMA::Unload("title", SOUND_MUSIC);
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
	SOMA::Load("Aud/Bgm_2.mp3", "gaem", SOUND_MUSIC);
	SOMA::SetSoundVolume(16);
	SOMA::SetMusicVolume(32);
	SOMA::PlayMusic("gaem", -1, 2000);

	XMLDocument xmlDoc;
	xmlDoc.LoadFile("SavedObjects.xml");
	XMLNode* pRoot = xmlDoc.FirstChildElement("Root");
	// Iterate through the Turret elements in the file and push_back new Turrets into the m_turrets vector.
	XMLElement* pElement = pRoot->FirstChildElement("GameObject");
	while (pElement != nullptr)
	{
		if (strcmp(pElement->Attribute("class"), "time") == 0)
		{
			int numebr;
			pElement->QueryIntAttribute("run_time ", &numebr);
			cout << "run time " << numebr << endl;
		}
		pElement = pElement->NextSiblingElement("longers time ");
	}



	TEMA::Load("Img/BG.png", "bg");
	m_vec.reserve(10);
	// Backgrounds.
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 0,0,600,768 }, { 0,0,1024,768 }, 1)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 0,0,600,768 }, { 1024,0,1024,768 }, 1)));
	// Midgrounds.
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,0,225,300}, { 0,0,256,512 }, 2)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,0,225,300}, { 256,0,256,512 }, 2)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,0,225,300}, { 512,0,256,512 }, 2)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,0,225,300}, { 768,0,256,512 }, 2)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,0,225,300}, { 1024,0,256,512 }, 2)));
	//// Foregrounds.
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,320,925,462 }, { 0,512,512,256 }, 4)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,320,925,462 }, { 512,512,512,256 }, 4)));
	m_vec.push_back(pair<string, GameObject*>("bg", new Background({ 700,320,925,462 }, { 1024,512,512,256 }, 4)));


	TEMA::Load("Img/Player.png", "player");
	m_objects.push_back(pair<string, GameObject*>("player", new PlatformPlayer({ 0,0,128,128 }, { 299,480,64,64 })));

	TEMA::Load("Img/ss.png", "ss");
	TEMA::Load("Img/button.png", "bs");
	//m_Bbox.push_back(pair<string, GameObject*>("bs", new Box({ 0,0,128,128 }, { WIDTH + 50,0 ,64,300 })));

	/*m_label.push_back(pair<string, GameObject*>("Label", new Label("Label",300,300,"works!!!!plz")));*/
}

void GameState::Update()
{
	
	m_Sbox.reserve(m_SboxNumber);
	for (int i = 0; i < m_SboxNumber; i++)
	{
		if (m_SspawnCtr++ % ScountNumber == 0)

		{
			m_SspawnCtr = 1;
			ScountNumber = (1 + rand() % 200) * 30;
			m_Sbox.push_back(pair<string, GameObject*>("ss", new Box({ 0,0,667,462 }, { WIDTH + 200,490 ,64,64 })));
			cout << ScountNumber << endl;
		}
		if (timercounter++ % counter == 0)
		{
			timercounter = 1;
			RunTime++;
			cout <<"time"<< RunTime << endl;
		}
	}
	for (auto const& i : m_Sbox)
	{
		for (size_t i = 0; i < m_Sbox.size(); i++)
		{
			m_Sbox[i].second->Update();

			if (m_Sbox[0].second != nullptr && m_Sbox[0].second->GetDst()->x <= -WIDTH)
			{

				delete m_Sbox[0].second;
				m_Sbox[0].second = nullptr;
				m_Sbox.erase(m_Sbox.begin());

			}
		}
	}


	m_Bbox.reserve(m_BboxNumber);
	for (int i = 0; i < m_BboxNumber; i++)
	{
		if (m_BspawnCtr++ % BcountNumber == 0)

		{
			m_BspawnCtr = 1;
			BcountNumber = (1 + rand() % 200) * 50;
			m_Bbox.push_back(pair<string, GameObject*>("bs", new Box({ 750,0,200,700 }, { WIDTH + 10,0 ,64,341 })));
			cout << BcountNumber << endl;
		}
	

	}
	for (auto const& i : m_Bbox)
	{
		for (size_t i = 0; i < m_Bbox.size(); i++)
		{
			m_Bbox[i].second->Update();

			if (m_Bbox[0].second != nullptr && m_Bbox[0].second->GetDst()->x <= -WIDTH)
			{

				delete m_Bbox[0].second;
				m_Bbox[0].second = nullptr;
				m_Bbox.erase(m_Bbox.begin());

			}
		}
	}

	if (BcountNumber!=0 && ScountNumber!=0 && BcountNumber == ScountNumber)
	{
		BcountNumber = (1 + rand() % 200) * 45;
		cout << "change b" << endl;
	}

	for (auto const& i : m_vec)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}

	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;

	}

	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState()); // Add new PauseState
	}

	


	//test collision
	//works
	PlatformPlayer* pObj = static_cast<PlatformPlayer*>(GetGo("player"));
	SDL_FRect* pBound = pObj->GetDst();
	Box* pBobj= static_cast<Box*>(GetGo("bs"));
	Box* pSobj = static_cast<Box*>(GetGo("ss"));
	for (size_t i = 0; i < m_Sbox.size(); i++)
	{
		SDL_FRect ePos = m_Sbox[i].second->m_dst;
		
		if (COMA::AABBCheck(*pBound, ePos))
		{
				cout << "player died" << endl;
				SOMA::PlaySound("exit");
				STMA::ChangeState(new LoseState());	
		}

	}

	for (size_t i = 0; i < m_Bbox.size(); i++)
	{
		SDL_FRect ePos = m_Bbox[i].second->m_dst;

		if (COMA::AABBCheck(*pBound, ePos))
		{
			SOMA::PlaySound("exit");
			cout << "player died" << endl;
			STMA::ChangeState(new LoseState());	
		}

	}

	if (pBound->y >450)
	{
		pObj->StopY();
		pObj->SetY(450);
		pObj->SetGrounded(true);
	}

	

	
	


	//used test files
	
	//if(COMA::AABBCheck(*pBound, *pBoxBound))
	//{
	//	cout << "player died" << endl;
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

	for (auto const& i : m_vec)
		i.second->Render();


	for (size_t i = 0; i < m_Sbox.size(); i++)
	{
		m_Sbox[i].second->Render();
	}

	for (size_t i = 0; i < m_Bbox.size(); i++)
	{
		m_Bbox[i].second->Render();
	}

	for (auto const& i : m_objects)
		i.second->Render();

	for (auto const& i : m_label)
		i.second->Render();

	if ( dynamic_cast<GameState*>(STMA::GetStates().back()) ) 
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

		XMLElement* pElement = xmlDoc.NewElement("GameObject");
		pElement->SetAttribute("class", "time");
		pElement->SetAttribute("run_time ",RunTime);
		pRoot->InsertEndChild(pElement);
		xmlDoc.SaveFile("SavedObjects.xml");


	TEMA::Unload( "bg");
	for (auto& i : m_vec)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_vec.clear();
	m_vec.shrink_to_fit();

	TEMA::Unload("player");
	for (auto& i : m_objects)
	{
		delete i.second; 
		i.second = nullptr;
	}
	m_objects.clear();
	m_objects.shrink_to_fit();


	TEMA::Unload("bs");
	for (size_t i = 0; i < m_Sbox.size(); i++)
	{
		delete m_Sbox[i].second;
		m_Sbox[i].second = nullptr;
	}
	m_Sbox.clear();
	m_Sbox.shrink_to_fit();


	TEMA::Unload("ss");
	for (size_t i = 0; i < m_Bbox.size(); i++)
	{
		delete m_Bbox[i].second;
		m_Bbox[i].second = nullptr;
	}
	m_Bbox.clear();
	m_Bbox.shrink_to_fit();

	
	SOMA::StopSound();
	SOMA::StopMusic();

}

void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
}


void GameState::deadtimer()
{
	
	time(&time_sec);              //获取当前秒数（1970-1-1 00:00:00到现在）
	printf("%02d\r", sec);
	old_sec = time_sec;           //更新旧的秒数
	while (sec > 0)
	{
		time(&time_sec);          //获取秒数保存到time_t变量
		if (time_sec != old_sec)   //如果秒数改变（计时达到1秒）
		{
			old_sec = time_sec;   //更新旧的秒数
			if (sec > 0)
			{
				sec++;            //计时秒数减1
			}
			printf("%02d\r", sec);
		}
	}
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

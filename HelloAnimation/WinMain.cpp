//====================================================================================================
// Filename:	WinMain.cpp
// Description:	Hello Animation demo.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

#include "Character.h"
#include "Character2.h"
#include "Map.h"
#include "time.h"
#include "FrontendState.h"
#include "GameplayState.h"
#include "CopLose.h"
#include "CopWin.h"
#include "CopWin2.h"

BaseState* currentState = nullptr;
GameState nextState = GameState::Invalid;
GameContext gameContext;

class TileMapGame : public Game
{
protected:
	virtual void OnInitializeImpl()
	{
		currentState = new FrontendState(gameContext);
		currentState->Load();
	}

	virtual void OnTerminateImpl()
	{
		currentState->Unload();
		delete currentState;
		currentState = nullptr;
	}

	virtual bool OnUpdateImpl(float dt)
	{
		// Check for state change
		if (nextState != GameState::Invalid)
		{
			currentState->Unload();
			delete currentState;
			currentState = nullptr;

			switch (nextState)
			{
			case GameState::Frontend:
				currentState = new FrontendState(gameContext);
				break;
			case GameState::Gameplay:
				currentState = new GameplayState(gameContext);
				break;
			case GameState::CopWin:
				currentState = new CopWin(gameContext);
				break;
			case GameState::CopLose:
				currentState = new CopLose(gameContext);
				break;
			case GameState::CopWin2:
				currentState = new CopWin2(gameContext);
				break;
			}

			currentState->Load();
		}

		nextState = currentState->Update(dt);
		return (nextState == GameState::Quit);
	}

	virtual void OnRenderImpl(float dt)
	{
		currentState->Render();
	}
};


Game* SGE_CreateGame()
{
	TileMapGame* game = new TileMapGame();
	return game;
}
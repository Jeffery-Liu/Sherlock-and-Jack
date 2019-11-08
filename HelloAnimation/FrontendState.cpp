#include "FrontendState.h"

FrontendState::FrontendState(GameContext& gc)
	: BaseState(gc)
{
}

FrontendState::~FrontendState()
{
}

void FrontendState::Load()
{
	FrontendMusic.Load("TitleMusic.mp3");
	FrontendMusic.Play(true);
	mBackground.Load("background2.png");
	mBackground.SetPosition(0.f, 0.f);
	mBackground.SetScale(0.75,0.8, false);
	mCursor.Load("sword.png");
	mFont.Load(72);
	mHelpControls.Load(24);
	mHelpControls.SetColor(0,0,0);
	mHelpLevel1.Load(24);
	mHelpLevel1.SetColor(0,0,0);
	mHelpLevel2.Load(24);
	mHelpLevel2.SetColor(0,0,0);
	Producer.Load(24);

	float posY = 500.0f;

	mStartButton.Load("button_on3.png", "button_off3.png");
	mStartButton.SetPosition(100.0f, posY);
	mStartButton.SetText("START", 0, 100, 255);

	posY += 50.0f;

	mLevelButton1.Load("button_on3.png", "button_off3.png");
	mLevelButton1.SetPosition(100.0f, posY);
	mLevelButton1.SetText("MISSION", 0, 100, 255);

	mLevelButton4.Load("button_on3.png", "button_off3.png");
	mLevelButton4.SetPosition(250.0f, posY);
	mLevelButton4.SetText("1 VS 1", 0, 100, 255);

	posY += 50.0f;

	mLevelButton2.Load("button_on3.png", "button_off3.png");
	mLevelButton2.SetPosition(100.0f, posY);
	mLevelButton2.SetText("ABILITIES", 0, 100, 255);

	mLevelButton5.Load("button_on3.png", "button_off3.png");
	mLevelButton5.SetPosition(250.0f, posY);
	mLevelButton5.SetText("2 VS 1", 0, 100, 255);

	posY += 50.0f;

	mLevelButton3.Load("button_on3.png", "button_off3.png");
	mLevelButton3.SetPosition(100.0f, posY);
	mLevelButton3.SetText("CONTROLS", 0, 100, 255);


	posY += 50.0f;

	mQuitButton.Load("button_on3.png", "button_off3.png");
	mQuitButton.SetPosition(100.0f, posY);
	mQuitButton.SetText("QUIT", 0, 100, 255);
}

void FrontendState::Unload()
{
	mCursor.Unload();
	mFont.Unload();
	mHelpControls.Unload();
	mHelpLevel1.Unload();
	mHelpLevel2.Unload();
	mBackground.Unload();
	mStartButton.Unload();
	mLevelButton1.Unload();
	mLevelButton2.Unload();
	mLevelButton3.Unload();
	mLevelButton4.Unload();
	mLevelButton5.Unload();
	mQuitButton.Unload();
	FrontendMusic.Stop();
	FrontendMusic.Unload();
	Producer.Unload();
}

GameState FrontendState::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mBackground.Update(deltaTime);
	mStartButton.Update(deltaTime);
	mLevelButton1.Update(deltaTime);
	mLevelButton2.Update(deltaTime);
	mLevelButton3.Update(deltaTime);
	mLevelButton4.Update(deltaTime);
	mLevelButton5.Update(deltaTime);
	mQuitButton.Update(deltaTime);
	

	GameState result = GameState::Invalid;
	if (mStartButton.IsPressed())
	{
		result = GameState::Gameplay;
	}
	else if (mLevelButton1.IsPressed())
	{
		//mGameContext.SetLevel(0);
		mHelpLevel1.SetText("SHERLOCK:\nSherlock Need to Catch\nJack in 60s.\n\nJACK:\nDo not be Caught by Sherlock.");
	}
	else if (mLevelButton2.IsPressed())
	{
		//mGameContext.SetLevel(1);
		mHelpLevel1.SetText("Active Ability:\nTAXI: Sherlock can call a taxi.\nTaxi can increase Sherlock's speed for 2s.\nCD:5s\n\nROADBLOCKS: John has 25 Roadblocks.\nRoadblocks can block players' movement.\n\nPassive Ability:\nInvisibility: Jack can be invisible for 2s.\nCD:1s");
			
	}
	else if (mLevelButton3.IsPressed())
	{
		mHelpLevel1.SetText("SHERLOCK: W, A, S, D keys to move.\nLeft Shift to call a taxi.\n\nJOHN: I, K, J, L keys to move.\nSpack key to place roadblocks.\n\nJACK: Arrow keys to move.");
	}
	else if (mLevelButton4.IsPressed())
	{
		mGameContext.SetLevel(0);
		mHelpLevel1.SetText("\n\n\n\n\n\n\n\n\nSHERLOCK vs JACK");
	}
	else if (mLevelButton5.IsPressed())
	{
		mGameContext.SetLevel(1);
		mHelpLevel1.SetText("\n\n\n\n\n\n\n\n\nSHERLOCK & JOHN\n            vs\n          JACK");
	}
	else if (mQuitButton.IsPressed())
	{
		result = GameState::Quit;
	}
	return result;
}

void FrontendState::Render()
{
	mBackground.Render();
	mFont.Print("Sherlock & Jack", 425, 100);
	mFont.SetColor(0,0,0);
	mStartButton.Render();
	mLevelButton1.Render();
	mLevelButton2.Render();
	mLevelButton3.Render();
	mLevelButton4.Render();
	mLevelButton5.Render();
	mQuitButton.Render();
	mCursor.Render();
	mHelpLevel1.Render(470,340);
	Producer.SetColor(0, 0, 0);
	Producer.Print("Copyright@ Jinfeng Liu", 1075, 0);
}

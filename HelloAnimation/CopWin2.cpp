#include "CopWin2.h"

CopWin2::CopWin2(GameContext& gc)
	: BaseState(gc)
{
}

CopWin2::~CopWin2()
{
}

void CopWin2::Load()
{
	CopWin2Music.Load("sherlock.mp3");
	CopWin2Music.Play(true);
	mBackground.Load("backgroundCopWin22.png");
	mBackground.SetPosition(0.f, 0.f);
	mBackground.SetScale(0.75, 0.8, false);
	mCursor.Load("sword.png");
	mFont.Load(72);
	mYesFont.Load(24);
	mYesFont.SetColor(0, 0, 0);
	mNoFont.Load(24);
	mNoFont.SetColor(0, 0, 0);
	mQuitFont.Load(24);
	mQuitFont.SetColor(0, 0, 0);
	Producer.Load(24);

	float posY = 500.0f;

	mYesButton.Load("button_on3.png", "button_off3.png");
	mYesButton.SetPosition(100.0f, posY);
	mYesButton.SetText("Yes", 0, 100, 255);

	posY += 50.0f;

	mNoButton.Load("button_on3.png", "button_off3.png");
	mNoButton.SetPosition(100.0f, posY);
	mNoButton.SetText("No", 0, 100, 255);

	posY += 100.0f;

	mQuitButton.Load("button_on3.png", "button_off3.png");
	mQuitButton.SetPosition(100.0f, posY);
	mQuitButton.SetText("QUIT", 0, 100, 255);
}

void CopWin2::Unload()
{
	mCursor.Unload();
	mFont.Unload();
	mYesFont.Unload();
	mNoFont.Unload();
	mQuitFont.Unload();
	mBackground.Unload();
	mYesButton.Unload();
	mNoButton.Unload();
	mQuitButton.Unload();
	CopWin2Music.Stop();
	CopWin2Music.Unload();
	Producer.Unload();
}

GameState CopWin2::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mBackground.Update(deltaTime);
	mYesButton.Update(deltaTime);
	mNoButton.Update(deltaTime);
	mQuitButton.Update(deltaTime);

	GameState result = GameState::Invalid;
	if (mYesButton.IsPressed())
	{
		result = GameState::Gameplay;
	}
	else if (mNoButton.IsPressed())
	{
		result = GameState::Frontend;
	}
	else if (mQuitButton.IsPressed())
	{
		result = GameState::Quit;
	}
	return result;
}

void CopWin2::Render()
{
	mBackground.Render();
	mFont.Print("       WINNER:\nSHERLOCK & JOHN!\n     New Game?", 375, 475);
	mFont.SetColor(100, 0, 0);
	mYesButton.Render();
	mNoButton.Render();
	mQuitButton.Render();
	mCursor.Render();
	mNoFont.Render(470, 340);
	Producer.SetColor(255, 255, 255);
	Producer.Print("Copyright@ Jinfeng Liu", 1075, 0);
}

#include "CopLose.h"

CopLose::CopLose(GameContext& gc)
	: BaseState(gc)
{
}

CopLose::~CopLose()
{
}

void CopLose::Load()
{
	CopLoseMusic.Load("pirates.wav");
	CopLoseMusic.Play(true);
	mBackground.Load("backgroundCopLose.png");
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

	mYesButton.Load("button_on2.png", "button_off2.png");
	mYesButton.SetPosition(100.0f, posY);
	mYesButton.SetText("Yes", 0, 100, 255);

	posY += 50.0f;

	mNoButton.Load("button_on2.png", "button_off2.png");
	mNoButton.SetPosition(100.0f, posY);
	mNoButton.SetText("No", 0, 100, 255);

	posY += 100.0f;

	mQuitButton.Load("button_on2.png", "button_off2.png");
	mQuitButton.SetPosition(100.0f, posY);
	mQuitButton.SetText("QUIT", 0, 100, 255);
}

void CopLose::Unload()
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
	CopLoseMusic.Stop();
	CopLoseMusic.Unload();
	Producer.Unload();
}

GameState CopLose::Update(float deltaTime)
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

void CopLose::Render()
{
	mBackground.Render();
	mFont.Print("WINNER:\nJACK SPARROW!\nNew Game?", 250, 50);
	mFont.SetColor(100, 0, 0);
	mYesButton.Render();
	mNoButton.Render();
	mQuitButton.Render();
	mCursor.Render();
	mNoFont.Render(470, 340);
	Producer.SetColor(0, 0, 0);
	Producer.Print("Copyright@ Jinfeng Liu", 1075, 0);
}

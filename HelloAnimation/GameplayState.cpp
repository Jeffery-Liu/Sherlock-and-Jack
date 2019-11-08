#include "GameplayState.h"
///////////////////////////////////////////////////
#include <SGE.h>
using namespace SGE;

#include "Character.h"
#include "Character2.h"
#include "Character3.h"
#include "Map.h"
#include "time.h"
#include "FrontendState.h"
#include "counter.h"
#include "RandomLevelGenerator.h"
//====================================================================================================
// Globals
//====================================================================================================

Character gCharacter;
Character2 gCharacter2;
Character3 gCharacter3;
Map gMap;
SGE_Font gFont;
SGE_Sound bgMusic;

bool john = false;

GameplayState::GameplayState(GameContext& gc)
	: BaseState(gc)
	, mpCharacter(nullptr)
{
}

GameplayState::~GameplayState()
{
}

void GameplayState::Load()
{
	mRLG.GetRandomLevel();
	GameCounter.Load(64);
	mCursor.Load("sword.png");
	//gCharacter2.Reset();
	gCharacter.Reset();
	gCharacter3.Reset();


	const int currentLevel = 0;
	const int Players = mGameContext.GetLevel();
	int RandomTex = rand() % 2;

	if (Players == 0)
	{
		john = false;
		gCharacter.Load();
		gCharacter.SetPosition(Vector2(1200.0f, 726.0f));

		gCharacter2.Load2();
		gCharacter2.SetPosition2(Vector2(110.0f, 115.0f));

		gCharacter3.Load3();
		gCharacter3.SetPosition3(Vector2(0.0f, 0.0f));

		if (RandomTex == 0)
		{
			gMap.Load("RandomLevelGenerator.txt", "texturepack01.txt");
		}
		else if(RandomTex == 1)
		{
			gMap.Load("RandomLevelGenerator.txt", "texturepack02.txt");
		}
		gFont.Load(24);

		int chooseMusic = 0;
		srand(time(NULL));
		chooseMusic = rand() % 2;
		if (chooseMusic == 0)
		{
			bgMusic.Load("pirates.wav");
		}
		else
		{
			bgMusic.Load("sherlock.mp3");
		}
		bgMusic.Play(true);
		NitrousCdPrint.Load(24);
		FlashPrint.Load(24);
	}
	if (Players == 1)
	{
		john = true;
		gCharacter.Load();
		gCharacter.SetPosition(Vector2(1200.0f, 726.0f));

		gCharacter2.Load2();
		gCharacter2.SetPosition2(Vector2(110.0f, 115.0f));

		gCharacter3.Load3();
		gCharacter3.SetPosition3(Vector2(125.0f, 100.0f));

		if (RandomTex == 0)
		{
			gMap.Load("RandomLevelGenerator.txt", "texturepack01.txt");
		}
		else if (RandomTex == 1)
		{
			gMap.Load("RandomLevelGenerator.txt", "texturepack02.txt");
		}
		gFont.Load(24);
		
		int chooseMusic = 0;
		srand(time(NULL));
		chooseMusic = rand() % 2;
		if(chooseMusic == 0)
		{
			bgMusic.Load("pirates.wav");
		}
		else
		{
			bgMusic.Load("sherlock.mp3");
		}
		bgMusic.Play(true);
		RbNumPrint.Load(24);
		NitrousCdPrint.Load(24);
		FlashPrint.Load(24);
	}
	Producer.Load(24);
	//-----------------------Game Timer------------------------
	GameTimer.Start(60.0f);
}

void GameplayState::Unload()
{
	mCursor.Unload();
	mMap.Unload();

	bgMusic.Stop();
	bgMusic.Unload();

	gCharacter.Unload();
	gCharacter2.Unload2();


	NitrousCdPrint.Unload();
	FlashPrint.Load(24);
	GameCounter.Unload();

	if (john == true)
	{
		gCharacter3.Unload3();
		RbNumPrint.Unload();
	}
	
	gMap.Unload();
	gFont.Unload();
	Producer.Unload();
}

GameState GameplayState::Update(float deltaTime)
{
	
	mCursor.Update(deltaTime);
	
	const Vector2 kTarget = gCharacter.GetPosition();

	const Vector2 kTarget2 = gCharacter2.GetPosition2();
	
	if (john == true)
	{
		const Vector2 kTarget3 = gCharacter3.GetPosition3();
	}

	const int kScreenWidth = IniFile_GetInt("WinWidth", 800);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 600);
	const int kMapWidth = gMap.GetWidth();
	const int kMapHeight = gMap.GetHeight();

	Vector2 offset;
	offset.x = (kScreenWidth * 0.5f) - kTarget.x;
	offset.x = Clamp(offset.x, (float)kScreenWidth - kMapWidth, 0.0f);
	offset.y = (kScreenHeight * 0.5f) - kTarget.y;
	offset.y = Clamp(offset.y, (float)kScreenHeight - kMapHeight, 0.0f);

	gCharacter.SetOffset(offset);
	gCharacter2.SetOffset2(offset);
	if (john == true)
	{
		gCharacter3.SetOffset3(offset);
	}
	gMap.SetOffset(offset);

	gCharacter.Update(deltaTime, gMap);
	gCharacter2.Update2(deltaTime, gMap);
	if (john == true)
	{
		gCharacter3.Update3(deltaTime, gMap);
	}
	gMap.Update(deltaTime);

	Rect bb = gCharacter.GetBoundingBox();
	Rect bb2 = gCharacter2.GetBoundingBox2();
	Rect bb3 = gCharacter3.GetBoundingBox3();

	bool isSherCatch = Physics_BoundingBoxTest(bb, bb2);
	bool isJohnCatch = Physics_BoundingBoxTest(bb, bb3);

	GameState result = GameState::Invalid;
	if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		result = GameState::Frontend;
	}
	else if (GameTimer.Update(deltaTime))
	{
		result = GameState::CopLose;		
	}
	else if(isSherCatch == true)
	{
		result = GameState::CopWin;
	}
	else if(isJohnCatch == true)
	{
		result = GameState::CopWin2;
	}
	return result;
}

void GameplayState::Render()
{
	gMap.Render();
	gCharacter.Render();
	gCharacter2.Render2();
	if (john == true)
	{
		gCharacter3.Render3();
	}

	// Print the game state.

	char Time[64];
	sprintf_s(Time, "%.0f", GameTimer.GetTime());
	GameCounter.SetColor(0, 100, 255);
	GameCounter.Print(Time, 610, 0);

	char Cd[64];
	sprintf_s(Cd, "Sherlock CD:%.1f", gCharacter2.GetCooldownTime());
	NitrousCdPrint.SetColor(255, 255, 255);
	NitrousCdPrint.Print(Cd, 25, 0);

	//char ACd[64];
	//sprintf_s(ACd, "Bullet:%.1f", gCharacter2.GetCooldownTime());
	//BulletsPrint.SetColor(255, 255, 255);
	//BulletsPrint.Print(ACd, 250, 0);

	char Num[64];
	sprintf_s(Num, "John Roadblock:%.0f", gCharacter3.GetRoadblock());
	RbNumPrint.SetColor(255, 255, 255);
	RbNumPrint.Print(Num, 420, 0);
	
	char FCd[64];
	sprintf_s(FCd, "Jack CD:%.1f", gCharacter.GetCooldownTime());
	FlashPrint.SetColor(255, 255, 255);
	FlashPrint.Print(FCd, 700, 0);

	char SCd[64];
	sprintf_s(SCd, "Spikes:%.0f", gCharacter.GetSpike());
	FlashPrint.SetColor(255, 255, 255);
	FlashPrint.Print(SCd, 850, 0);

	Producer.SetColor(255, 255, 255);
	Producer.Print("Copyright@ Jinfeng Liu", 1075, 0);

	//gFont.Print(gameTime, 0, 0);
	//gFont.Print(gCharacter.GetCurrentState(), 0, 30);
	//gFont.Print(gCharacter2.GetCurrentState2(), 0, 80);
	//gFont.Print(gCharacter3.GetCurrentState3(), 0, 130);
}


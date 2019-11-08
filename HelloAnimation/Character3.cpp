//====================================================================================================
// Filename:	Character3.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Character3.h"

#include "CharacterFall3.h"
#include "CharacterIdle3.h"
#include "CharacterJump3.h"
#include "CharacterWalk3.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Character3::Character3()
	: mpCurrentState3(nullptr)
	, mPosition3(0.0f, 0.0f)
	, mVelocity3(0.0f, 0.0f)
	, mOffset3(0.f, 0.f)
	, mFacingLeft3(false)
{
	memset(mCharacterStates3, 0, sizeof(CharacterState3*) * AS_Max3);

	Reset();
}

//-------------------------------------------------------------

Character3::~Character3()
{
	// Empty
}

void Character3::Reset()
{
	//nitrous = false;
	roadblock = kMaxRoadblocks;
	for(int i = 0; i < kMaxRoadblocks; i++)
	{
		pendingRoadblocks[i].Reset();
	}
	mRoadblockNum = kMaxRoadblocks;
}

//--------------------------------------------------------------

void Character3::Load3()
{
	// Clear everything
	Unload3();

	// Create character states
	mCharacterStates3[AS_Idle3] = new CharacterIdle3(this);
	mCharacterStates3[AS_Walk3] = new CharacterWalk3(this);
	mCharacterStates3[AS_Jump3] = new CharacterJump3(this);
	mCharacterStates3[AS_Fall3] = new CharacterFall3(this);

	// Load state resources
	for (int i = 0; i < AS_Max3; ++i)
	{
		mCharacterStates3[i]->Load3();
	}

	// Set default state
	ChangeState3(AS_Idle3);
	AbilityTimer.Start(5.0f);
	CooldownTimer.Start(5.0f);
}

//-------------------------------------------------------------

void Character3::Unload3()
{
	for (int i = 0; i < AS_Max3; ++i)
	{
		if (mCharacterStates3[i] != nullptr)
		{
			mCharacterStates3[i]->Unload3();
			delete mCharacterStates3[i];
			mCharacterStates3[i] = nullptr;
		}
	}
	mpCurrentState3 = nullptr;
}

//-------------------------------------------------------------

void Character3::Update3(float deltaTime, Map& map)
{
	// Update the current state
	mpCurrentState3->Update3(deltaTime);

	float movementCost = map.GetIntersectingAvgMovementCost(GetBoundingBox3());

	//-----------------------Movement cost-------------------------------------------------------------------------------------------------------------
	mVelocity3 /= Clamp(movementCost * kMovementCostScalar, 1.0f, 10.0f);
	//-------------------------------------------------------------------------------------------------------------------------------------------------

	//------cop's ability trigger----------------------------------------------------------------------------------------------------------------------

	//---------Set ROADBLOCKS--------------------------------------------
	
	if(roadblock > 0)
	{
		if (Input_IsKeyPressed(Keys::SPACE))
		{
			const float screenX = mPosition3.x;
			const float screenY = mPosition3.y;
			Tile& tile = map.GetTile(screenX, screenY);
			map.SetTileType(tile, 21);
	
			roadblock--;
			pushPendingRoadblocks(tile.GetIndex());
			
			mRoadblockNum = roadblock;
		}
	}
	
	for(int i = 0; i < kMaxRoadblocks; ++i)
	{
		if(pendingRoadblocks[i].mTileIndex != -1)
		{
			if(pendingRoadblocks[i].mTimer.Update(deltaTime) == true)
			{
				Tile& tile = map.GetTile(pendingRoadblocks[i].mTileIndex);
				map.SetTileType(tile,28);
				pendingRoadblocks[i].mTileIndex = -1;
			}
		}
	}

	// Apply movement
	CheckCollision3(deltaTime, map);
}

void Character3::pushPendingRoadblocks(int tile)
{
	for(int i = 0; i < kMaxRoadblocks; i++)
	{
		if(pendingRoadblocks[i].mTileIndex == -1)
		{
			pendingRoadblocks[i].mTileIndex = tile;
			pendingRoadblocks[i].mTimer.Start(kRoadblockPendingTime);
			break;
		}
		 
	}
}

//--------------------------------------------------------------------
void Character3::Render3()
{
	mpCurrentState3->Render3(mOffset3);
	
	Rect bb = GetBoundingBox3();
	Graphics_DebugRect(bb + mOffset3, 0xff0000);
}

//--------------------------------------------------------------------
void Character3::ChangeState3(AnimationState3 as)
{
	// Check if we are already in this state
	if (mpCurrentState3 == mCharacterStates3[as])
	{
		return;
	}

	// Exit the current state
	if (mpCurrentState3 != nullptr)
	{
		mpCurrentState3->Exit3();
	}

	// Switch to the new state
	mpCurrentState3 = mCharacterStates3[as];

	// Enter the new state
	if (mpCurrentState3 != nullptr)
	{
		mpCurrentState3->Enter3();
	}
}

//---------------------------------------------------------------------

const char* Character3::GetCurrentState3()
{
	const char* name = "Unknown";
	if (mpCurrentState3 != nullptr)
	{
		name = mpCurrentState3->GetName3();
	}
	return name;
}

//---------------------------------------------------------------------

Rect Character3::GetBoundingBox3() const
{

	return mpCurrentState3->GetBoundingBox3();
}

//---------------------------------------------------------------------
void Character3::CheckCollision3(float deltaTime, const Map& map)
{
	// Check collision
	Rect bb = GetBoundingBox3();
	Rect newbb = bb + Vector2(mVelocity3.x, 0.0f);
	Rect rightbb = map.GetBoundingBoxFromSegment(newbb.GetRightSegment());
	Rect leftbb = map.GetBoundingBoxFromSegment(newbb.GetLeftSegment());

	// Right collision
	if (mVelocity3.x > 0.0f && rightbb.IsValid())
	{
		mPosition3.x += static_cast<int>(rightbb.min.x - bb.max.x) - 1.0f;
	}
	// Left collision
	else if (mVelocity3.x < 0.0f && leftbb.IsValid())
	{
		mPosition3.x += static_cast<int>(leftbb.max.x - bb.min.x) + 1.0f;
	}
	else
	{
		mPosition3.x += static_cast<int>(mVelocity3.x);
	}

	// Check collision
	newbb = bb + Vector2(0.0f, mVelocity3.y);
	Rect bottombb = map.GetBoundingBoxFromSegment(newbb.GetBottomSegment());
	Rect topbb = map.GetBoundingBoxFromSegment(newbb.GetTopSegment());

	// Bottom collision
	if (mVelocity3.y > 0.0f && bottombb.IsValid())
	{
		mPosition3.y = bottombb.min.y - 1.0f;
		mVelocity3.y = 0.0f;
	}
	// Top collision
	else if (mVelocity3.y < 0.0f && topbb.IsValid())
	{
		mPosition3.y += static_cast<int>(topbb.max.y - bb.min.y) + 1.0f;
		mVelocity3.y = 0.0f;
	}
	else
	{
		mPosition3.y += static_cast<int>(mVelocity3.y);
		
	}
}
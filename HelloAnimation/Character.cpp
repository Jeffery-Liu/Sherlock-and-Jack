//====================================================================================================
// Filename:	Character.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Character.h"

#include "CharacterFall.h"
#include "CharacterIdle.h"
#include "CharacterJump.h"
#include "CharacterWalk.h"


//====================================================================================================
// Class Definitions
//====================================================================================================


Character::Character()
	: mpCurrentState(nullptr)
	, mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mOffset(0.f, 0.f)
	, mFacingLeft(false)
	, invisible(false)
{
	memset(mCharacterStates, 0, sizeof(CharacterState*) * AS_Max);

	Reset();
}

//----------------------------------------------------------------------------------------------------

Character::~Character()
{
	// Empty
}

void Character::Reset()
{
	flash = false;
	Spike = kMaxSpikes;
	for (int i = 0; i < kMaxSpikes; i++)
	{
		pendingSpikes[i].Reset();
	}
	mSpikeNum = kMaxSpikes;
}

//----------------------------------------------------------------------------------------------------

void Character::Load()
{
	// Clear everything
	Unload();
	// Create character states
	mCharacterStates[AS_Idle] = new CharacterIdle(this);
	mCharacterStates[AS_Walk] = new CharacterWalk(this);
	mCharacterStates[AS_Jump] = new CharacterJump(this);
	mCharacterStates[AS_Fall] = new CharacterFall(this);

	// Load state resources
	for (int i = 0; i < AS_Max; ++i)
	{
		mCharacterStates[i]->Load();
	}

	// Set default state
	ChangeState(AS_Idle);

	// Ability time  Invisible time
	AbilityTimer.Start(2.0f);
	CooldownTimer.Start(1.0f);

	// Flash time
	AbilityTimer2.Start(0.1f);
	CooldownTimer2.Start(10.0f);
}

//----------------------------------------------------------------------------------------------------

void Character::Unload()
{
	for (int i = 0; i < AS_Max; ++i)
	{
		if (mCharacterStates[i] != nullptr)
		{
			mCharacterStates[i]->Unload();
			delete mCharacterStates[i];
			mCharacterStates[i] = nullptr;
		}
	}
	mpCurrentState = nullptr;
}

//----------------------------------------------------------------------------------------------------

void Character::Update(float deltaTime,  Map& map)
{
	// Update the current state
	mpCurrentState->Update(deltaTime);

	float movementCost = map.GetIntersectingAvgMovementCost(GetBoundingBox());
	
	//-----------------------Movement cost-------------------------------------------------------------------------------------------------------------
	mVelocity /= Clamp(movementCost * kMovementCostScalar, 1.0f, 10.0f);
	//-------------------------------------------------------------------------------------------------------------------------------------------------


	//-------Thief's ability trigger------------------------------------------
	
	if(!invisible)
	{
		if(CooldownTimer.Update(deltaTime))
		{
			invisible = true;
		}
	}
	else
	{
		if(AbilityTimer.Update(deltaTime))
		{
			invisible = false;
		}
	}

	//------Flash ability--------------------------------------------------------------------------------------------------------

	if (!flash)
	{
		if (CooldownTimer2.Update(deltaTime))
		{
			flash = true;
		}
	}
	else
	{
		if (Input_IsKeyDown(Keys::NUM_DECIMAL))
		{
			mVelocity *= 5.0f;
			if (AbilityTimer2.Update(deltaTime))
			{
				flash = false;
			}
		}
	}
	mCooldownTime = CooldownTimer2.GetTime();

	//---------Set Spikes--------------------------------------------

	if (Spike > 0)
	{
		if (Input_IsKeyPressed(Keys::NUMPAD0))
		{
			const float screenX = mPosition.x;
			const float screenY = mPosition.y;
			Tile& tile = map.GetTile(screenX, screenY);
			map.SetTileType(tile, 32);

			Spike--;
			pushPendingSpikes(tile.GetIndex());

			mSpikeNum = Spike;
		}
	}

	for (int i = 0; i < kMaxSpikes; ++i)
	{
		if (pendingSpikes[i].mTileIndex != -1)
		{
			if (pendingSpikes[i].mTimer.Update(deltaTime) == true)
			{
				Tile& tile = map.GetTile(pendingSpikes[i].mTileIndex);
				map.SetTileType(tile, 31);
				pendingSpikes[i].mTileIndex = -1;
			}
		}
	}

	CheckCollision(deltaTime, map);
}

void Character::pushPendingSpikes(int tile)
{
	for (int i = 0; i < kMaxSpikes; i++)
	{
		if (pendingSpikes[i].mTileIndex == -1)
		{
			pendingSpikes[i].mTileIndex = tile;
			pendingSpikes[i].mTimer.Start(kSpikePendingTime);
			break;
		}

	}
}

void Character::Render()
{
	if (!invisible)
	{
		mpCurrentState->Render(mOffset);
	
		Rect bb = GetBoundingBox();
		Graphics_DebugRect(bb + mOffset, 0xff0000);
	}
	
}

//----------------------------------------------------------------------------------------------------

void Character::ChangeState(AnimationState as)
{
	// Check if we are already in this state
	if (mpCurrentState == mCharacterStates[as])
	{
		return;
	}

	// Exit the current state
	if (mpCurrentState != nullptr)
	{
		mpCurrentState->Exit();
	}

	// Switch to the new state
	mpCurrentState = mCharacterStates[as];

	// Enter the new state
	if (mpCurrentState != nullptr)
	{
		mpCurrentState->Enter();
	}
}

//----------------------------------------------------------------------------------------------------

const char* Character::GetCurrentState()
{
	const char* name = "Unknown";
	if (mpCurrentState != nullptr)
	{
		name = mpCurrentState->GetName();
	}
	return name;
}

//----------------------------------------------------------------------------------------------------

Rect Character::GetBoundingBox() const
{
	return mpCurrentState->GetBoundingBox();
}

//----------------------------------------------------------------------------------------------------

void Character::CheckCollision(float deltaTime, const Map& map)
{
	// Check collision
	Rect bb = GetBoundingBox();
	Rect newbb = bb + Vector2(mVelocity.x, 0.0f);
	Rect rightbb = map.GetBoundingBoxFromSegment(newbb.GetRightSegment());
	Rect leftbb = map.GetBoundingBoxFromSegment(newbb.GetLeftSegment());

	// Right collision
	if (mVelocity.x > 0.0f && rightbb.IsValid())
	{
		mPosition.x += static_cast<int>(rightbb.min.x - bb.max.x) - 1.0f;
	}
	// Left collision
	else if (mVelocity.x < 0.0f && leftbb.IsValid())
	{
		mPosition.x += static_cast<int>(leftbb.max.x - bb.min.x) + 1.0f;
	}
	else
	{
		mPosition.x += static_cast<int>(mVelocity.x);
	}

	// Check collision
	newbb = bb + Vector2(0.0f, mVelocity.y);
	Rect bottombb = map.GetBoundingBoxFromSegment(newbb.GetBottomSegment());
	Rect topbb = map.GetBoundingBoxFromSegment(newbb.GetTopSegment());

	// Bottom collision
	if (mVelocity.y > 0.0f && bottombb.IsValid())
	{
		mPosition.y += static_cast<int>(bottombb.min.y - bb.max.y) - 1.0f;
		//mPosition.y = bottombb.min.y - 1.0f;
		mVelocity.y = 0.0f;
	}
	// Top collision
	else if (mVelocity.y < 0.0f && topbb.IsValid())
	{
		mPosition.y += static_cast<int>(topbb.max.y - bb.min.y) + 1.0f;
		mVelocity.y = 0.0f;
	}
	else
	{
		mPosition.y += static_cast<int>(mVelocity.y);
		
	}
}

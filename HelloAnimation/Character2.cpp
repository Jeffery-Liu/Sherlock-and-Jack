//====================================================================================================
// Filename:	Character2.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Character2.h"

#include "CharacterFall2.h"
#include "CharacterIdle2.h"
#include "CharacterJump2.h"
#include "CharacterWalk2.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

Character2::Character2()
	: mpCurrentState2(nullptr)
	, mPosition2(0.0f, 0.0f)
	, mVelocity2(0.0f, 0.0f)
	, mOffset2(0.f, 0.f)
	, mFacingLeft2(false)
{
	memset(mCharacterStates2, 0, sizeof(CharacterState2*) * AS_Max2);

	Reset();
}

//-------------------------------------------------------------

Character2::~Character2()
{
	// Empty
}

void Character2::Reset()
{
	nitrous = false;
}

//--------------------------------------------------------------

void Character2::Load2()
{
	// Clear everything
	Unload2();

	// Create character states
	mCharacterStates2[AS_Idle2] = new CharacterIdle2(this);
	mCharacterStates2[AS_Walk2] = new CharacterWalk2(this);
	mCharacterStates2[AS_Jump2] = new CharacterJump2(this);
	mCharacterStates2[AS_Fall2] = new CharacterFall2(this);

	// Load state resources
	for (int i = 0; i < AS_Max2; ++i)
	{
		mCharacterStates2[i]->Load2();
	}

	// Sherlock's Ability's Timer:
	ChangeState2(AS_Idle2);
	AbilityTimer.Start(2.0f);
	CooldownTimer.Start(5.0f);
}

//-------------------------------------------------------------

void Character2::Unload2()
{
	for (int i = 0; i < AS_Max2; ++i)
	{
		if (mCharacterStates2[i] != nullptr)
		{
			mCharacterStates2[i]->Unload2();
			delete mCharacterStates2[i];
			mCharacterStates2[i] = nullptr;
		}
	}
	mpCurrentState2 = nullptr;
}

//-------------------------------------------------------------

void Character2::Update2(float deltaTime, Map& map)
{
	// Update the current state
	mpCurrentState2->Update2(deltaTime);

	float movementCost = map.GetIntersectingAvgMovementCost(GetBoundingBox2());

	//-----------------------Movement cost-------------------------------------------------------------------------------------------------------------
	mVelocity2 /= Clamp(movementCost * kMovementCostScalar, 1.0f, 10.0f);
	//-------------------------------------------------------------------------------------------------------------------------------------------------

	//------cop's ability trigger----------------------------------------------------------------------------------------------------------------------

	//------NITROUS ability---nitrous-----------------------------------------------------------------------------------------------------

	if(!nitrous)
	{
		if(CooldownTimer.Update(deltaTime))
		{
			nitrous = true;
		}
	}
	else
	{
		if(Input_IsKeyDown(Keys::LSHIFT))
		{
			mVelocity2 *= 1.75f;
			if(AbilityTimer.Update(deltaTime))
			{
				nitrous = false;
			}
		}
	}
	mCooldownTime = CooldownTimer.GetTime();

	// Apply movement
	CheckCollision2(deltaTime, map);
}

//--------------------------------------------------------------------
void Character2::Render2()
{
	mpCurrentState2->Render2(mOffset2);
	
	Rect bb = GetBoundingBox2();
	Graphics_DebugRect(bb + mOffset2, 0xff0000);
}

//--------------------------------------------------------------------
void Character2::ChangeState2(AnimationState2 as)
{
	// Check if we are already in this state
	if (mpCurrentState2 == mCharacterStates2[as])
	{
		return;
	}

	// Exit the current state
	if (mpCurrentState2 != nullptr)
	{
		mpCurrentState2->Exit2();
	}

	// Switch to the new state
	mpCurrentState2 = mCharacterStates2[as];

	// Enter the new state
	if (mpCurrentState2 != nullptr)
	{
		mpCurrentState2->Enter2();
	}
}

//---------------------------------------------------------------------

const char* Character2::GetCurrentState2()
{
	const char* name = "Unknown";
	if (mpCurrentState2 != nullptr)
	{
		name = mpCurrentState2->GetName2();
	}
	return name;
}

//---------------------------------------------------------------------

Rect Character2::GetBoundingBox2() const
{

	return mpCurrentState2->GetBoundingBox2();
}

//---------------------------------------------------------------------
void Character2::CheckCollision2(float deltaTime, const Map& map)
{
	// Check collision
	Rect bb = GetBoundingBox2();
	Rect newbb = bb + Vector2(mVelocity2.x, 0.0f);
	Rect rightbb = map.GetBoundingBoxFromSegment(newbb.GetRightSegment());
	Rect leftbb = map.GetBoundingBoxFromSegment(newbb.GetLeftSegment());

	// Right collision
	if (mVelocity2.x > 0.0f && rightbb.IsValid())
	{
		mPosition2.x += static_cast<int>(rightbb.min.x - bb.max.x) - 1.0f;
	}
	// Left collision
	else if (mVelocity2.x < 0.0f && leftbb.IsValid())
	{
		mPosition2.x += static_cast<int>(leftbb.max.x - bb.min.x) + 1.0f;
	}
	else
	{
		mPosition2.x += static_cast<int>(mVelocity2.x);
	}

	// Check collision
	newbb = bb + Vector2(0.0f, mVelocity2.y);
	Rect bottombb = map.GetBoundingBoxFromSegment(newbb.GetBottomSegment());
	Rect topbb = map.GetBoundingBoxFromSegment(newbb.GetTopSegment());

	// Bottom collision
	if (mVelocity2.y > 0.0f && bottombb.IsValid())
	{
		mPosition2.y = bottombb.min.y - 1.0f;
		mVelocity2.y = 0.0f;
	}
	// Top collision
	else if (mVelocity2.y < 0.0f && topbb.IsValid())
	{
		mPosition2.y += static_cast<int>(topbb.max.y - bb.min.y) + 1.0f;
		mVelocity2.y = 0.0f;
	}
	else
	{
		mPosition2.y += static_cast<int>(mVelocity2.y);
		
	}
}
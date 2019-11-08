//====================================================================================================
// Filename:	CharacterWalk.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterWalk.h"

#include "Character.h"

#include "CharacterState.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterWalk::CharacterWalk(Character* pOwner)
	: CharacterState(pOwner, "Walk")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterWalk::~CharacterWalk()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Load()
{
	mSprite.Add("pirate_right1.png");
	mSprite.Add("pirate_right3.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Update(float deltaTime)
{
	// Update sprite
	mSprite.Update(deltaTime);
	// Normal movement
	if (Input_IsKeyDown(Keys::UP))
	{
		mpOwner->ChangeState(AS_Jump);
	}

	else if (Input_IsKeyDown(Keys::DOWN))
	{
		mpOwner->ChangeState(AS_Fall);
	}
	
	else if (Input_IsKeyDown(Keys::RIGHT))
	{
		Vector2 vel(kSpeed * deltaTime, 0.0f);
		mpOwner->SetVelocity(vel);
		mpOwner->SetFacingLeft(false);
	}
	else if (Input_IsKeyDown(Keys::LEFT))
	{
		Vector2 vel(-kSpeed * deltaTime, 0.0f);
		mpOwner->SetVelocity(vel);
		mpOwner->SetFacingLeft(true);
	}
	// Flash skill
	else if (Input_IsKeyDown(Keys::UP) && Input_IsKeyDown(Keys::RCONTROL))
	{
		mpOwner->ChangeState(AS_Jump);
	}

	else if (Input_IsKeyDown(Keys::DOWN) && Input_IsKeyDown(Keys::RCONTROL))
	{
		mpOwner->ChangeState(AS_Fall);
	}

	else if (Input_IsKeyDown(Keys::RIGHT) && Input_IsKeyDown(Keys::RCONTROL))
	{
		Vector2 vel(kSpeed * deltaTime, 0.0f);
		mpOwner->SetVelocity(vel);
		mpOwner->SetFacingLeft(false);
	}
	else if (Input_IsKeyDown(Keys::LEFT) && Input_IsKeyDown(Keys::RCONTROL))
	{
		Vector2 vel(-kSpeed * deltaTime, 0.0f);
		mpOwner->SetVelocity(vel);
		mpOwner->SetFacingLeft(true);
	}
	else
	{
		mpOwner->SetVelocity(Vector2());
		mpOwner->ChangeState(AS_Idle);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Render(const Vector2& offset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	const Vector2 ownerPos(mpOwner->GetPosition());
	const Vector2 renderPos(ownerPos.x - (kTextureWidth * 0.5f), ownerPos.y - kTextureHeight);
	bool facingLeft = mpOwner->IsFacingLeft();
	mSprite.SetPosition(renderPos + offset);
	mSprite.SetFlipH(facingLeft);
	mSprite.Render();
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Enter()
{
	mSprite.Play(1.0f/0.25f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

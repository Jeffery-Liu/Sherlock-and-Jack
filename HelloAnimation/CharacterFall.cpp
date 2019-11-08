//====================================================================================================
// Filename:	CharacterFall.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterFall.h"

#include "Character.h"

#include "CharacterState.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterFall::CharacterFall(Character* pOwner)
	: CharacterState(pOwner, "DOWN")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterFall::~CharacterFall()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Load()
{
	mSprite.Add("pirate_down1.png");
	mSprite.Add("pirate_down3.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Update(float deltaTime)
{
	// Update sprite
	mSprite.Update(deltaTime);
	
	if (Input_IsKeyDown(Keys::DOWN))
	{
		Vector2 vel(0.0f, kSpeed * deltaTime);
		mpOwner->SetVelocity(vel);
	}
	else
	{
		mpOwner->SetVelocity(Vector2());
		mpOwner->ChangeState(AS_Idle);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Render(const Vector2& offset)
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

void CharacterFall::Enter()
{
	mSprite.Play(1.0f/0.25f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterFall::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

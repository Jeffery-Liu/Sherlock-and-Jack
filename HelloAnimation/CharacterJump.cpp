//====================================================================================================
// Filename:	CharacterJump.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterJump.h"

#include "Character.h"

#include "CharacterState.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterJump::CharacterJump(Character* pOwner)
	: CharacterState(pOwner, "UP")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterJump::~CharacterJump()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Load()
{
	mSprite.Add("pirate_up1.png");
	mSprite.Add("pirate_up3.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Update(float deltaTime)
{
	// Update sprite
	mSprite.Update(deltaTime);
	
	if (Input_IsKeyDown(Keys::UP))
	{
		Vector2 vel(0.0f, -kSpeed * deltaTime);
		mpOwner->SetVelocity(vel);
	}
	else
	{
		mpOwner->SetVelocity(Vector2());
		mpOwner->ChangeState(AS_Idle);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Render(const Vector2& offset)
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

void CharacterJump::Enter()
{
	mSprite.Play(1.0f/0.25f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterJump::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

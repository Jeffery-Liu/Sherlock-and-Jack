//====================================================================================================
// Filename:	CharacterIdle.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterIdle.h"

#include "Character.h"

#include "CharacterState.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterIdle::CharacterIdle(Character* pOwner)
	: CharacterState(pOwner, "Idle")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterIdle::~CharacterIdle()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Load()
{
	mSprite.Add("pirate_left2.png");
	mSprite.Add("pirate_right2.png");
	mSprite.Add("pirate_left2.png");
	mSprite.Add("pirate_right2.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Unload()
{
	mSprite.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Update(float deltaTime)
{
	// Update sprite
	mSprite.Update(deltaTime);

	// State transitions
	if (Input_IsKeyPressed(Keys::UP))
	{
		mpOwner->ChangeState(AS_Jump);
	}
	else if (Input_IsKeyPressed(Keys::DOWN))
	{
		mpOwner->ChangeState(AS_Fall);
	}
	else if (Input_IsKeyDown(Keys::RIGHT) || Input_IsKeyDown(Keys::LEFT))
	{
		mpOwner->ChangeState(AS_Walk);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Render(const Vector2& offset)
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

void CharacterIdle::Enter()
{
	mSprite.Play(1.0f/0.5f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle::Exit()
{
	mSprite.Stop();
	mSprite.Reset();
}

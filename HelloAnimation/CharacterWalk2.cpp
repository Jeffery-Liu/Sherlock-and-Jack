//====================================================================================================
// Filename:	CharacterWalk2.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterWalk2.h"

#include "Character2.h"

#include "CharacterState2.h"

#include "Map.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterWalk2::CharacterWalk2(Character2* pOwner)
	: CharacterState2(pOwner, "Walk")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterWalk2::~CharacterWalk2()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk2::Load2()
{
	mSprite2.Add("sherlock_right1.png");
	mSprite2.Add("sherlock_right3.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk2::Unload2()
{
	mSprite2.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk2::Update2(float deltaTime)
{
	// Update sprite
	mSprite2.Update(deltaTime);

	

	if (Input_IsKeyDown(Keys::W))
	{
		mpOwner2->ChangeState2(AS_Jump2);
	}

	else if (Input_IsKeyDown(Keys::S))
	{
		mpOwner2->ChangeState2(AS_Fall2);
	}
	

	else if (Input_IsKeyDown(Keys::D))
	{
		Vector2 vel(kSpeed2 * deltaTime, 0.0f);
		mpOwner2->SetVelocity2(vel);
		mpOwner2->SetFacingLeft2(false);
	}
	else if (Input_IsKeyDown(Keys::A))
	{
		Vector2 vel(-kSpeed2 * deltaTime, 0.0f);
		mpOwner2->SetVelocity2(vel);
		mpOwner2->SetFacingLeft2(true);
	}
	else
	{
		mpOwner2->SetVelocity2(Vector2());
		mpOwner2->ChangeState2(AS_Idle2);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk2::Render2(const Vector2& offset)
{
	const int kTextureWidth2 = mSprite2.GetWidth();
	const int kTextureHeight2 = mSprite2.GetHeight();
	const Vector2 ownerPos2(mpOwner2->GetPosition2());
	const Vector2 renderPos2(ownerPos2.x - (kTextureWidth2 * 0.5f), ownerPos2.y - kTextureHeight2);
	bool facingLeft2 = mpOwner2->IsFacingLeft2();
	mSprite2.SetPosition(renderPos2 + offset);
	mSprite2.SetFlipH(facingLeft2);
	mSprite2.Render();
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk2::Enter2()
{
	mSprite2.Play(1.0f/0.25f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk2::Exit2()
{
	mSprite2.Stop();
	mSprite2.Reset();
}

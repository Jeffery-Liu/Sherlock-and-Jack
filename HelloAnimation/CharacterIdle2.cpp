//====================================================================================================
// Filename:	CharacterIdle2.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterIdle2.h"

#include "Character2.h"

#include "CharacterState2.h"

#include "Map.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterIdle2::CharacterIdle2(Character2* pOwner2)
	: CharacterState2(pOwner2, "Idle")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterIdle2::~CharacterIdle2()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle2::Load2()
{
	mSprite2.Add("sherlock_left2.png");
	mSprite2.Add("sherlock_right2.png");
	mSprite2.Add("sherlock_left2.png");
	mSprite2.Add("sherlock_right2.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle2::Unload2()
{
	mSprite2.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle2::Update2(float deltaTime)
{
	// Update sprite
	mSprite2.Update(deltaTime);

	// State transitions
	if (Input_IsKeyPressed(Keys::W))
	{
		mpOwner2->ChangeState2(AS_Jump2);
	}
	else if (Input_IsKeyPressed(Keys::S))
	{
		mpOwner2->ChangeState2(AS_Fall2);
	}
	else if (Input_IsKeyDown(Keys::D) || Input_IsKeyDown(Keys::A))
	{
		mpOwner2->ChangeState2(AS_Walk2);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle2::Render2(const Vector2& offset)
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

void CharacterIdle2::Enter2()
{
	mSprite2.Play(1.0f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle2::Exit2()
{
	mSprite2.Stop();
	mSprite2.Reset();
}

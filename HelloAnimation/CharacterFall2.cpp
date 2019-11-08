//====================================================================================================
// Filename:	CharacterFall2.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterFall2.h"

#include "Character2.h"

#include "CharacterState2.h"

#include "Map.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterFall2::CharacterFall2(Character2* pOwner2)
	: CharacterState2(pOwner2, "DOWN")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterFall2::~CharacterFall2()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterFall2::Load2()
{
	mSprite2.Add("sherlock_down1.png");
	mSprite2.Add("sherlock_down3.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterFall2::Unload2()
{
	mSprite2.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterFall2::Update2(float deltaTime)
{
	// Update sprite
	mSprite2.Update(deltaTime);
	
	if (Input_IsKeyDown(Keys::S))
	{
		Vector2 vel(0.0f, kSpeed2 * deltaTime);
		mpOwner2->SetVelocity2(vel);
	}
	else
	{
		mpOwner2->SetVelocity2(Vector2());
		mpOwner2->ChangeState2(AS_Idle2);
	}

}

//----------------------------------------------------------------------------------------------------

void CharacterFall2::Render2(const Vector2& offset)
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

void CharacterFall2::Enter2()
{
	mSprite2.Play(1.0f/0.25f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterFall2::Exit2()
{
	mSprite2.Stop();
	mSprite2.Reset();
}

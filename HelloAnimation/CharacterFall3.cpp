//====================================================================================================
// Filename:	CharacterFall3.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterFall3.h"

#include "Character3.h"

#include "CharacterState3.h"

#include "Map.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterFall3::CharacterFall3(Character3* pOwner3)
	: CharacterState3(pOwner3, "DOWN")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterFall3::~CharacterFall3()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterFall3::Load3()
{
	mSprite3.Add("john_down1.png");
	mSprite3.Add("john_down3.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterFall3::Unload3()
{
	mSprite3.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterFall3::Update3(float deltaTime)
{
	// Update sprite
	mSprite3.Update(deltaTime);
	
	if (Input_IsKeyDown(Keys::K))
	{
		Vector2 vel(0.0f, kSpeed3 * deltaTime);
		mpOwner3->SetVelocity3(vel);
	}
	else
	{
		mpOwner3->SetVelocity3(Vector2());
		mpOwner3->ChangeState3(AS_Idle3);
	}

}

//----------------------------------------------------------------------------------------------------

void CharacterFall3::Render3(const Vector2& offset)
{
	const int kTextureWidth3 = mSprite3.GetWidth();
	const int kTextureHeight3 = mSprite3.GetHeight();
	const Vector2 ownerPos3(mpOwner3->GetPosition3());
	const Vector2 renderPos3(ownerPos3.x - (kTextureWidth3 * 0.5f), ownerPos3.y - kTextureHeight3);
	bool facingLeft3 = mpOwner3->IsFacingLeft3();
	mSprite3.SetPosition(renderPos3 + offset);
	mSprite3.SetFlipH(facingLeft3);
	mSprite3.Render();
}

//----------------------------------------------------------------------------------------------------

void CharacterFall3::Enter3()
{
	mSprite3.Play(1.0f/0.25f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterFall3::Exit3()
{
	mSprite3.Stop();
	mSprite3.Reset();
}

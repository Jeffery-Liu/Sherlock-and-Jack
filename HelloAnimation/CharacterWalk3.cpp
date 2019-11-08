//====================================================================================================
// Filename:	CharacterWalk3.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterWalk3.h"

#include "Character3.h"

#include "CharacterState3.h"

#include "Map.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterWalk3::CharacterWalk3(Character3* pOwner)
	: CharacterState3(pOwner, "Walk")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterWalk3::~CharacterWalk3()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk3::Load3()
{
	mSprite3.Add("john_right1.png");
	mSprite3.Add("john_right3.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk3::Unload3()
{
	mSprite3.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk3::Update3(float deltaTime)
{
	// Update sprite
	mSprite3.Update(deltaTime);

	

	if (Input_IsKeyDown(Keys::I))
	{
		mpOwner3->ChangeState3(AS_Jump3);
	}

	else if (Input_IsKeyDown(Keys::K))
	{
		mpOwner3->ChangeState3(AS_Fall3);
	}
	

	else if (Input_IsKeyDown(Keys::L))
	{
		Vector2 vel(kSpeed3 * deltaTime, 0.0f);
		mpOwner3->SetVelocity3(vel);
		mpOwner3->SetFacingLeft3(false);
	}
	else if (Input_IsKeyDown(Keys::J))
	{
		Vector2 vel(-kSpeed3 * deltaTime, 0.0f);
		mpOwner3->SetVelocity3(vel);
		mpOwner3->SetFacingLeft3(true);
	}
	else
	{
		mpOwner3->SetVelocity3(Vector2());
		mpOwner3->ChangeState3(AS_Idle3);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk3::Render3(const Vector2& offset)
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

void CharacterWalk3::Enter3()
{
	mSprite3.Play(1.0f/0.25f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterWalk3::Exit3()
{
	mSprite3.Stop();
	mSprite3.Reset();
}

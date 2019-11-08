//====================================================================================================
// Filename:	CharacterIdle3.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterIdle3.h"

#include "Character3.h"

#include "CharacterState3.h"

#include "Map.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CharacterIdle3::CharacterIdle3(Character3* pOwner3)
	: CharacterState3(pOwner3, "Idle")
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CharacterIdle3::~CharacterIdle3()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle3::Load3()
{

	mSprite3.Add("john_left2.png");
	mSprite3.Add("john_right2.png");
	mSprite3.Add("john_left2.png");
	mSprite3.Add("john_right2.png");
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle3::Unload3()
{
	mSprite3.Unload();
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle3::Update3(float deltaTime)
{
	// Update sprite
	mSprite3.Update(deltaTime);

	// State transitions
	if (Input_IsKeyPressed(Keys::I))
	{
		mpOwner3->ChangeState3(AS_Jump3);
	}
	else if (Input_IsKeyPressed(Keys::K))
	{
		mpOwner3->ChangeState3(AS_Fall3);
	}
	else if (Input_IsKeyDown(Keys::L) || Input_IsKeyDown(Keys::J))
	{
		mpOwner3->ChangeState3(AS_Walk3);
	}
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle3::Render3(const Vector2& offset)
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

void CharacterIdle3::Enter3()
{
	mSprite3.Play(1.0f, true);
}

//----------------------------------------------------------------------------------------------------

void CharacterIdle3::Exit3()
{
	mSprite3.Stop();
	mSprite3.Reset();
}

#ifndef INCLUDED_CHARACTER2_H
#define INCLUDED_CHARACTER2_H

//====================================================================================================
// Filename:	Character2.h
// Description:	Class for a character.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

#include "CharacterState2.h"
#include "Map.h"
#include "Tile.h"
#include "counter.h"

//====================================================================================================
// Enums
//====================================================================================================

enum AnimationState2
{
	AS_None2 = -1,
	AS_Idle2,
	AS_Walk2,
	AS_Jump2,
	AS_Fall2,
	AS_Max2
};

//====================================================================================================
// Class Declarations
//====================================================================================================

class Character2
{
public:
	Character2();
	~Character2();

	void Reset();

	void Load2();
	void Unload2();
	void Update2(float deltaTime, Map& map);
	void Render2();

	void ChangeState2(AnimationState2 as);
	const char* GetCurrentState2();

	Rect GetBoundingBox2() const;

	// Accessors
	const Vector2& GetPosition2() const		{ return mPosition2; }
	const Vector2& GetVelocity2() const		{ return mVelocity2; }
	const Vector2& GetOffset2() const		{ return mOffset2; }
	bool IsFacingLeft2() const				{ return mFacingLeft2; }

	// Mutators
	void SetPosition2(const Vector2& pos)	{ mPosition2 = pos; }
	void SetVelocity2(const Vector2& vel)	{ mVelocity2 = vel; }
	void SetOffset2(const Vector2& offset)	{ mOffset2 = offset; }
	void SetFacingLeft2(bool facingLeft)		{ mFacingLeft2 = facingLeft; }

	//-----------------------------------------------------
	float GetCooldownTime() { return (mCooldownTime - 55.0); }
	//-----------------------------------------------------

private:
	void CheckCollision2(float deltaTime, const Map& map);

	CharacterState2* mCharacterStates2[AS_Max2];
	CharacterState2* mpCurrentState2;

	Vector2 mPosition2;
	Vector2 mVelocity2;
	Vector2 mOffset2;

	bool mFacingLeft2;
	bool nitrous;
	Counter AbilityTimer;
	Counter CooldownTimer;

	float mCooldownTime;
	//---------------------------------------------------------------------------------------	
	const float kMovementCostScalar = 0.75f;
};



	

#endif // #ifndef INCLUDED_CHARACTER_H
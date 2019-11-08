#ifndef INCLUDED_CHARACTER3_H
#define INCLUDED_CHARACTER3_H

//====================================================================================================
// Filename:	Character3.h
// Description:	Class for a character.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

#include "CharacterState3.h"
#include "Map.h"
#include "Tile.h"
#include "counter.h"

//====================================================================================================
// Enums
//====================================================================================================

enum AnimationState3
{
	AS_None3 = -1,
	AS_Idle3,
	AS_Walk3,
	AS_Jump3,
	AS_Fall3,
	AS_Max3
};

//====================================================================================================
// Class Declarations
//====================================================================================================

class Character3
{
public:
	Character3();
	~Character3();

	void Reset();

	void Load3();
	void Unload3();
	void Update3(float deltaTime, Map& map);
	void Render3();

	void ChangeState3(AnimationState3 as);
	const char* GetCurrentState3();

	Rect GetBoundingBox3() const;

	// Accessors
	const Vector2& GetPosition3() const		{ return mPosition3; }
	const Vector2& GetVelocity3() const		{ return mVelocity3; }
	const Vector2& GetOffset3() const		{ return mOffset3; }
	bool IsFacingLeft3() const				{ return mFacingLeft3; }

	// Mutators
	void SetPosition3(const Vector2& pos)	{ mPosition3 = pos; }
	void SetVelocity3(const Vector2& vel)	{ mVelocity3 = vel; }
	void SetOffset3(const Vector2& offset)	{ mOffset3 = offset; }
	void SetFacingLeft3(bool facingLeft)		{ mFacingLeft3 = facingLeft; }

	//-----------------------------------------------------
	float GetRoadblock() { return (mRoadblockNum); }
	//-----------------------------------------------------

private:
	void CheckCollision3(float deltaTime, const Map& map);
	void pushPendingRoadblocks(int tile);
	//----------------------------------------------------
	float mRoadblockNum = kMaxRoadblocks;

	struct PendingRoadblock
	{
		PendingRoadblock()	{ Reset(); }

		void Reset()
		{
			mTileIndex = -1;
		}

		int mTileIndex;
		Counter mTimer;
	};

	static const int kMaxRoadblocks = 25;
	const float kRoadblockPendingTime = 1.f;

	CharacterState3* mCharacterStates3[AS_Max3];
	CharacterState3* mpCurrentState3;

	Vector2 mPosition3;
	Vector2 mVelocity3;
	Vector2 mOffset3;

	PendingRoadblock pendingRoadblocks[kMaxRoadblocks];

	bool mFacingLeft3;
	Counter AbilityTimer;
	Counter CooldownTimer;

	//----------------------Roadblock setting-----------------------------------
	int roadblock;

	//---------------------------------------------------------------------------------------
	const float kMovementCostScalar = 0.75f;
};



	

#endif // #ifndef INCLUDED_CHARACTER_H
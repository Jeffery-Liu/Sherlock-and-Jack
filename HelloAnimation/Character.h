#ifndef INCLUDED_CHARACTER_H
#define INCLUDED_CHARACTER_H

//====================================================================================================
// Filename:	Character.h
// Description:	Class for a character.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

#include "CharacterState.h"
#include "Map.h"
#include "counter.h"
#include "Tile.h"


//====================================================================================================
// Enums
//====================================================================================================

enum AnimationState
{
	AS_None = -1,
	AS_Idle,
	AS_Walk,
	AS_Jump,
	AS_Fall,
	AS_Max
};

//====================================================================================================
// Class Declarations
//====================================================================================================

class Character
{
public:
	Character();
	~Character();

	void Reset();

	void Load();
	void Unload();
	void Update(float deltaTime, Map& map);
	void Render();

	void ChangeState(AnimationState as);
	const char* GetCurrentState();

	Rect GetBoundingBox() const;

	// Accessors
	const Vector2& GetPosition() const		{ return mPosition; }
	const Vector2& GetVelocity() const		{ return mVelocity; }
	const Vector2& GetOffset() const		{ return mOffset; }
	bool IsFacingLeft() const				{ return mFacingLeft; }
	bool IsInvisible()  const				{ return invisible; }

	// Mutators
	void SetPosition(const Vector2& pos)	{ mPosition = pos; }
	void SetVelocity(const Vector2& vel)	{ mVelocity = vel; }
	void SetOffset(const Vector2& offset)	{ mOffset = offset; }
	void SetFacingLeft(bool facingLeft)		{ mFacingLeft = facingLeft; }
	void SetInvisible(bool flag)			{ invisible = flag; }

	//-----------------------------------------------------
	float GetCooldownTime() { return (mCooldownTime - 50.0); }
	//-----------------------------------------------------

	//-----------------------------------------------------
	float GetSpike() { return (mSpikeNum); }
	//-----------------------------------------------------
private:
	void CheckCollision(float deltaTime, const Map& map);

	//----------------------Spike setting-----------------------------------------
	int Spike;
	static const int kMaxSpikes = 25;
	float mSpikeNum = kMaxSpikes;
	void pushPendingSpikes(int tile);

	struct PendingSpike
	{
		PendingSpike() { Reset(); }

		void Reset()
		{
			mTileIndex = -1;
		}

		int mTileIndex;
		Counter mTimer;
	};

	const float kSpikePendingTime = 1.f;
	PendingSpike pendingSpikes[kMaxSpikes];

	CharacterState* mCharacterStates[AS_Max];
	CharacterState* mpCurrentState;

	Vector2 mPosition;
	Vector2 mVelocity;
	Vector2 mOffset;

	bool mFacingLeft;
	bool invisible;

	bool flash;

	Counter AbilityTimer;
	Counter CooldownTimer;

	Counter AbilityTimer2;
	Counter CooldownTimer2;
	
	float mCooldownTime;
	//---------------------------------------------------------------------------------------
	const float kMovementCostScalar = 0.75f;
	//-----------------------------------------------------------------------------------------

	
};


#endif // #ifndef INCLUDED_CHARACTER_H
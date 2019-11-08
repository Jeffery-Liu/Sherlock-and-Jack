#ifndef INCLUDED_CHARACTERSTATE_H
#define INCLUDED_CHARACTERSTATE_H

//====================================================================================================
// Filename:	CharacterState.h
// Description:	Class for a character state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Character;

//====================================================================================================
// Class Declarations
//====================================================================================================

// Change the speed here
const float kSpeed = 250.0f;
// Flash speed


class CharacterState
{
public:
	CharacterState(Character* pOwner, const char* name) : mpOwner(pOwner), mName(name) {}
	virtual ~CharacterState() {};

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(const Vector2& offset) = 0;

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	Rect GetBoundingBox() const;

	const char* GetName() const	{ return mName; }

protected:
	SGE_Sprite mSprite;

	Character* mpOwner;

	const char* mName;
};

#endif // #ifndef INCLUDED_CHARACTERSTATE_H
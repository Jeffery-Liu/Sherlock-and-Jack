#ifndef INCLUDED_CHARACTERSTATE3_H
#define INCLUDED_CHARACTERSTATE3_H

//====================================================================================================
// Filename:	CharacterState3.h
// Description:	Class for a character state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
#include "Map.h"

using namespace SGE;

//====================================================================================================
// Forward Declarations
//====================================================================================================

class Character3;

//====================================================================================================
// Class Declarations
//====================================================================================================


// Change the speed here
	const float kSpeed3 = 150.0f;

class CharacterState3
{
public:
	CharacterState3(Character3* pOwner, const char* name) : mpOwner3(pOwner), mName3(name) {}
	virtual ~CharacterState3() {};

	virtual void Load3() = 0;
	virtual void Unload3() = 0;
	virtual void Update3(float deltaTime) = 0;
	virtual void Render3(const Vector2& offset) = 0;

	virtual void Enter3() = 0;
	virtual void Exit3() = 0;

	Rect GetBoundingBox3() const;

	const char* GetName3() const	{ return mName3; }

protected:
	SGE_Sprite mSprite3;

	Character3* mpOwner3;

	const char* mName3;
};


#endif // #ifndef INCLUDED_CHARACTERSTATE_H
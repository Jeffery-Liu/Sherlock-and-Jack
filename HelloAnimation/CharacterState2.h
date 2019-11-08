#ifndef INCLUDED_CHARACTERSTATE2_H
#define INCLUDED_CHARACTERSTATE2_H

//====================================================================================================
// Filename:	CharacterState2.h
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

class Character2;

//====================================================================================================
// Class Declarations
//====================================================================================================


// Change the speed here
	const float kSpeed2 = 200.0f;

class CharacterState2// : public Map
{
public:
	CharacterState2(Character2* pOwner, const char* name) : mpOwner2(pOwner), mName2(name) {}
	virtual ~CharacterState2() {};

	virtual void Load2() = 0;
	virtual void Unload2() = 0;
	virtual void Update2(float deltaTime) = 0;
	virtual void Render2(const Vector2& offset) = 0;

	virtual void Enter2() = 0;
	virtual void Exit2() = 0;

	Rect GetBoundingBox2() const;

	const char* GetName2() const	{ return mName2; }

protected:
	SGE_Sprite mSprite2;

	Character2* mpOwner2;

	const char* mName2;
};


#endif // #ifndef INCLUDED_CHARACTERSTATE_H
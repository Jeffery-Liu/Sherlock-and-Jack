#ifndef INCLUDED_CHARACTERWALK2_H
#define INCLUDED_CHARACTERWALK2_H

//====================================================================================================
// Filename:	CharacterWalk2.h
// Description:	Class for the character walk state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterWalk2 : public CharacterState2
{
public:
	CharacterWalk2(Character2* pOwner);
	virtual ~CharacterWalk2();

	virtual void Load2();
	virtual void Unload2();
	virtual void Update2(float deltaTime);
	virtual void Render2(const Vector2& offset);

	virtual void Enter2();
	virtual void Exit2();
};

#endif // #ifndef INCLUDED_CHARACTERWALK_H
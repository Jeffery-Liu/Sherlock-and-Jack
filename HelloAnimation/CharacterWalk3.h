#ifndef INCLUDED_CHARACTERWALK3_H
#define INCLUDED_CHARACTERWALK3_H

//====================================================================================================
// Filename:	CharacterWalk3.h
// Description:	Class for the character walk state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState3.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterWalk3 : public CharacterState3
{
public:
	CharacterWalk3(Character3* pOwner);
	virtual ~CharacterWalk3();

	virtual void Load3();
	virtual void Unload3();
	virtual void Update3(float deltaTime);
	virtual void Render3(const Vector2& offset);

	virtual void Enter3();
	virtual void Exit3();
};

#endif // #ifndef INCLUDED_CHARACTERWALK_H
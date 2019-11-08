#ifndef INCLUDED_CHARACTERJUMP3_H
#define INCLUDED_CHARACTERJUMP3_H

//====================================================================================================
// Filename:	CharacterJump3.h
// Description:	Class for the character jump state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState3.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterJump3 : public CharacterState3
{
public:
	CharacterJump3(Character3* pOwner);
	virtual ~CharacterJump3();

	virtual void Load3();
	virtual void Unload3();
	virtual void Update3(float deltaTime);
	virtual void Render3(const Vector2& offset);

	virtual void Enter3();
	virtual void Exit3();
};

#endif // #ifndef INCLUDED_CHARACTERJUMP_H
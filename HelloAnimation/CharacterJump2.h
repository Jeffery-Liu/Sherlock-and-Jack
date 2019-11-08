#ifndef INCLUDED_CHARACTERJUMP2_H
#define INCLUDED_CHARACTERJUMP2_H

//====================================================================================================
// Filename:	CharacterJump2.h
// Description:	Class for the character jump state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterJump2 : public CharacterState2
{
public:
	CharacterJump2(Character2* pOwner);
	virtual ~CharacterJump2();

	virtual void Load2();
	virtual void Unload2();
	virtual void Update2(float deltaTime);
	virtual void Render2(const Vector2& offset);

	virtual void Enter2();
	virtual void Exit2();
};

#endif // #ifndef INCLUDED_CHARACTERJUMP_H
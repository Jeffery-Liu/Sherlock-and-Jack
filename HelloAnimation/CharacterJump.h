#ifndef INCLUDED_CHARACTERJUMP_H
#define INCLUDED_CHARACTERJUMP_H

//====================================================================================================
// Filename:	CharacterJump.h
// Description:	Class for the character jump state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterJump : public CharacterState
{
public:
	CharacterJump(Character* pOwner);
	virtual ~CharacterJump();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float deltaTime);
	virtual void Render(const Vector2& offset);

	virtual void Enter();
	virtual void Exit();
};

#endif // #ifndef INCLUDED_CHARACTERJUMP_H
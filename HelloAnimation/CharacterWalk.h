#ifndef INCLUDED_CHARACTERWALK_H
#define INCLUDED_CHARACTERWALK_H

//====================================================================================================
// Filename:	CharacterWalk.h
// Description:	Class for the character walk state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterWalk : public CharacterState
{
public:
	CharacterWalk(Character* pOwner);
	virtual ~CharacterWalk();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float deltaTime);
	virtual void Render(const Vector2& offset);

	virtual void Enter();
	virtual void Exit();
};

#endif // #ifndef INCLUDED_CHARACTERWALK_H
#ifndef INCLUDED_CHARACTERFALL_H
#define INCLUDED_CHARACTERFALL_H

//====================================================================================================
// Filename:	CharacterFall.h
// Description:	Class for the character fall state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterFall : public CharacterState
{
public:
	CharacterFall(Character* pOwner);
	virtual ~CharacterFall();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float deltaTime);
	virtual void Render(const Vector2& offset);

	virtual void Enter();
	virtual void Exit();
};

#endif // #ifndef INCLUDED_CHARACTERFALL_H
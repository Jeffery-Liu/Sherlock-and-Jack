#ifndef INCLUDED_CHARACTERIDLE_H
#define INCLUDED_CHARACTERIDLE_H

//====================================================================================================
// Filename:	CharacterIdle.h
// Created by:	Peter Chan
// Description:	Class for the character idle state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterIdle : public CharacterState
{
public:
	CharacterIdle(Character* pOwner);
	virtual ~CharacterIdle();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float deltaTime);
	virtual void Render(const Vector2& offset);

	virtual void Enter();
	virtual void Exit();
};

#endif // #ifndef INCLUDED_CHARACTERIDLE_H
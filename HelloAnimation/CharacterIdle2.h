#ifndef INCLUDED_CHARACTERIDLE2_H
#define INCLUDED_CHARACTERIDLE2_H

//====================================================================================================
// Filename:	CharacterIdle2.h
// Created by:	Peter Chan
// Description:	Class for the character idle state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterIdle2 : public CharacterState2
{
public:
	CharacterIdle2(Character2* pOwner2);
	virtual ~CharacterIdle2();

	virtual void Load2();
	virtual void Unload2();
	virtual void Update2(float deltaTime);
	virtual void Render2(const Vector2& offset);

	virtual void Enter2();
	virtual void Exit2();
};

#endif // #ifndef INCLUDED_CHARACTERIDLE_H
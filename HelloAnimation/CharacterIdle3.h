#ifndef INCLUDED_CHARACTERIDLE3_H
#define INCLUDED_CHARACTERIDLE3_H

//====================================================================================================
// Filename:	CharacterIdle3.h
// Created by:	Peter Chan
// Description:	Class for the character idle state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState3.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterIdle3 : public CharacterState3
{
public:
	CharacterIdle3(Character3* pOwner3);
	virtual ~CharacterIdle3();

	virtual void Load3();
	virtual void Unload3();
	virtual void Update3(float deltaTime);
	virtual void Render3(const Vector2& offset);

	virtual void Enter3();
	virtual void Exit3();
};

#endif // #ifndef INCLUDED_CHARACTERIDLE_H
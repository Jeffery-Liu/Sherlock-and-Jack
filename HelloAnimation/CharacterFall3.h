#ifndef INCLUDED_CHARACTERFALL3_H
#define INCLUDED_CHARACTERFALL3_H

//====================================================================================================
// Filename:	CharacterFall3.h
// Description:	Class for the character fall state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState3.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterFall3 : public CharacterState3
{
public:
	CharacterFall3(Character3* pOwner3);
	virtual ~CharacterFall3();

	virtual void Load3();
	virtual void Unload3();
	virtual void Update3(float deltaTime);
	virtual void Render3(const Vector2& offset);

	virtual void Enter3();
	virtual void Exit3();
};

#endif // #ifndef INCLUDED_CHARACTERFALL_H
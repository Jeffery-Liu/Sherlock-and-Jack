#ifndef INCLUDED_CHARACTERFALL2_H
#define INCLUDED_CHARACTERFALL2_H

//====================================================================================================
// Filename:	CharacterFall2.h
// Description:	Class for the character fall state.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CharacterState2.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class CharacterFall2 : public CharacterState2
{
public:
	CharacterFall2(Character2* pOwner2);
	virtual ~CharacterFall2();

	virtual void Load2();
	virtual void Unload2();
	virtual void Update2(float deltaTime);
	virtual void Render2(const Vector2& offset);

	virtual void Enter2();
	virtual void Exit2();
};

#endif // #ifndef INCLUDED_CHARACTERFALL_H
#ifndef INCLUDED_GAMEPLAYSTATE_H
#define INCLUDED_GAMEPLAYSTATE_H

#include "BaseState.h"
#include "Character.h"
#include "counter.h"
#include "Map.h"
#include "Character.h"
#include "Character2.h"
#include "Character3.h"
#include "RandomLevelGenerator.h"

class GameplayState : public BaseState
{
public:
	GameplayState(GameContext& gc);
	~GameplayState();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual GameState Update(float deltaTime);
	virtual void Render();
	
private:
	SGE_Cursor mCursor;
	SGE_Font FlashPrint; // Flash CD
	SGE_Font NitrousCdPrint; //Nitrous Cooldown Time Print
	//SGE_Font BulletsPrint;
	SGE_Font RbNumPrint;  //Rocdblocks Number Print
	SGE_Font GameCounter;
	SGE_Font Producer;
	Character* mpCharacter;
	Map mMap;
	RandomLevelGenerator mRLG;

	Counter GameTimer;
	
	bool isSherCatch = false;
	bool isJohnCatch = false;
};

#endif // #ifndef INCLUDED_GAMEPLAYSTATE_H
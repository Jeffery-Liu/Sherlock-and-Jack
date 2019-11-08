#ifndef INCLUDED_CopLose_H
#define INCLUDED_CopLose_H

#include <SGE.h>
using namespace SGE;

#include "BaseState.h"

class CopLose : public BaseState
{
public:
	CopLose(GameContext& gc);
	~CopLose();

	// Implements BaseState
	virtual void Load();
	virtual void Unload();
	virtual GameState Update(float deltaTime);
	virtual void Render();

private:
	SGE_Cursor mCursor;
	SGE_Font mFont;
	SGE_Font Producer;
	SGE_Sprite mBackground;
	SGE_Button mYesButton;
	SGE_Button mNoButton;
	SGE_Button mQuitButton;
	SGE_Font mYesFont;
	SGE_Font mNoFont;
	SGE_Font mQuitFont;
	SGE_Sound CopLoseMusic;

	
};

#endif // #ifndef INCLUDED_CopLose_H
#ifndef INCLUDED_CopWin2_H
#define INCLUDED_CopWin2_H

#include <SGE.h>
using namespace SGE;

#include "BaseState.h"

class CopWin2 : public BaseState
{
public:
	CopWin2(GameContext& gc);
	~CopWin2();

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
	SGE_Sound CopWin2Music;

};

#endif // #ifndef INCLUDED_CopWin2_H
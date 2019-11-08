#ifndef INCLUDED_FRONTENDSTATE_H
#define INCLUDED_FRONTENDSTATE_H

#include <SGE.h>
using namespace SGE;

#include "BaseState.h"

class FrontendState : public BaseState
{
public:
	FrontendState(GameContext& gc);
	~FrontendState();

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
	SGE_Button mStartButton;
	SGE_Button mLevelButton1;
	SGE_Button mLevelButton2;
	SGE_Button mLevelButton3;
	SGE_Button mLevelButton4;
	SGE_Button mLevelButton5;
	SGE_Button mQuitButton;
	SGE_Font mHelpControls;
	SGE_Font mHelpLevel1;
	SGE_Font mHelpLevel2;
	SGE_Sound FrontendMusic;
};

#endif // #ifndef INCLUDED_FRONTENDSTATE_H
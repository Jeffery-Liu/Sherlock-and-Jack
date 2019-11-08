#ifndef INCLUDED_GAMESTATES_H
#define INCLUDED_GAMESTATES_H

enum class GameState
{
	Invalid,
	Frontend,
	Gameplay,
	Quit,
	CopWin,
	CopLose,
	CopWin2
};

#endif // #ifndef INCLUDED_GAMESTATES_H
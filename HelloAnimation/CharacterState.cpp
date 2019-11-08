#include "CharacterState.h"
#include "Character.h"

Rect CharacterState::GetBoundingBox() const
{
	const Vector2 pos(mpOwner->GetPosition());
		return Rect
		(
		// Change the size of charactor HERE
			pos.x - 5.0f,
			pos.y - 15.0f,
			pos.x + 5.0f,
			pos.y
		);
}
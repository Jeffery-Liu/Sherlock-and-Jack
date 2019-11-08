#include "CharacterState2.h"
#include "Character2.h"

Rect CharacterState2::GetBoundingBox2() const
{
	const Vector2 pos2(mpOwner2->GetPosition2());
		return Rect
		(
		// Change the size of charactor HERE
			pos2.x - 5.0f,
			pos2.y - 15.0f,
			pos2.x + 5.0f,
			pos2.y
		);
}
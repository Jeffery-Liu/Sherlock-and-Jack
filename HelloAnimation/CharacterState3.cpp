#include "CharacterState3.h"
#include "Character3.h"

Rect CharacterState3::GetBoundingBox3() const
{
	const Vector2 pos3(mpOwner3->GetPosition3());
		return Rect
		(
		// Change the size of charactor HERE
			pos3.x - 5.0f,
			pos3.y - 15.0f,
			pos3.x + 5.0f,
			pos3.y
		);
}
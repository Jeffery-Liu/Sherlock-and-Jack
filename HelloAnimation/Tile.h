#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

#include <SGE.h>
using namespace SGE;

class Tile
{
public:
	Tile();
	~Tile();

	Rect GetBoundingBox() const;
	
	const Vector2& GetPosition() const		{ return mPosition; }
	int GetSize() const						{ return mSize; }
	int GetIndex() const					{ return mIndex; }
	bool IsWalkable() const					{ return mWalkable; }
	int GetType() const						{ return mType; }
	int GetMovementCost() const				{ return mMovementCost; }
	int GetDamage() const					{ return mDamage; }

	void SetPosition(const Vector2& pos)	{ mPosition = pos; }
	void SetSize(int size)					{ mSize = size; }
	void SetWalkable(bool walkable)			{ mWalkable = walkable; }
	void SetMovementCost(int cost)			{ mMovementCost = cost; }
	void SetDamage(int damage)				{ mDamage = damage; }

private:
	friend class Map;

	void SetType(int type)					{ mType = type; }

	Vector2 mPosition;
	int mSize;
	int mIndex;
	int mType;
	int mMovementCost;
	int mDamage;
	bool mWalkable;
};

#endif // #ifndef INCLUDED_TILE_H
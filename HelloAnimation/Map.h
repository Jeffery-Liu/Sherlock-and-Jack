#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

#include <SGE.h>
using namespace SGE;
#include "Tile.h"

class Map
{
public:
	Map();
	~Map();

	void Load(const char* pLevelFile, const char* pTexturePack);
	void Unload();
	void Update(float deltaTime);
	void Render();

	Tile& GetTile(int screenX, int screenY);
	Tile& GetTile(const Vector2& screenPos);
	Tile& GetTile(int index);

	void SetTileType(Tile& tile, int type);

	Rect GetBoundingBoxFromSegment(const LineSegment& line) const;
	Rect GetIntersectingRegion(const Rect& bb) const;
	float GetIntersectingAvgMovementCost(const Rect& bb) const;

	int IncrementTileType(int currentType);
	int DecrementTileType(int currentType);

	void StartPathfinding();
	void EndPathfinding();
	void GetTileNeighbors(int tileIndex, std::vector<int>& neighborsOut);

	int GetWidth() const	{ return mColumns * mTileSize; }
	int GetHeight() const	{ return mRows * mTileSize; }

	void SetOffset(const Vector2& offset)	{ mOffset = offset; }
	Vector2 GetOffset() const				{ return mOffset; }

private:
	bool LoadLevel(const char* pLevelFile);
	bool LoadTexturePack(const char* pTexturePack);

	SGE_Sprite* mSprites;
	Tile* mTiles;
	Tile* mTilePrototypes;
	Vector2 mOffset;

	int mColumns;
	int mRows;
	int mTileSize;
	int mTileCount;
	int mSpriteCount;
	bool mFlipNeighborOrder;
	
	Tile tile;


	//mVelocity /= Clamp(movementCost * kMovementCostScalar, 1.0f, 10.0f);
};


#endif // #ifndef INCLUDED_MAP_H
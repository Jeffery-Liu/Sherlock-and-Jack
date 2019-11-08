#include "Map.h"

Map::Map()
	: mSprites(nullptr)
	, mTiles(nullptr)
	, mTilePrototypes(nullptr)
	, mOffset(0.f, 0.f)
	, mColumns(0)
	, mRows(0)
	, mTileSize(0)
	, mTileCount(0)
	, mSpriteCount(0)
	, mFlipNeighborOrder(false)
{
	// Empty
}

Map::~Map()
{
	// Empty
}

void Map::Load(const char* pLevelFile, const char* pTexturePack)
{
	// Clean up before we start loading anything
	Unload();

	// Load level data
	if (!LoadLevel(pLevelFile))
	{
		Unload();
		return;
	}

	// Load texture pack
	if (!LoadTexturePack(pTexturePack))
	{
		Unload();
		return;
	}
}

void Map::Unload()
{
	if (mSprites != nullptr)
	{
		for (int i = 0; i < mSpriteCount; ++i)
		{
			mSprites[i].Unload();
		}
		delete[] mSprites;
		mSprites = nullptr;
	}

	if(mTilePrototypes != nullptr)
	{
		delete[] mTilePrototypes;
		mTilePrototypes = nullptr;
	}

	if (mTiles != nullptr)
	{
		delete[] mTiles;
		mTiles = nullptr;
	}

	// Reset params
	mColumns = 0;
	mRows = 0;
	mTileSize = 0;
	mTileCount = 0;
	mSpriteCount = 0;
}

void Map::Update(float deltaTime)
{
	// Do nothing
}

void Map::Render()
{
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = x + (y * mColumns);
			const Tile& tile = mTiles[index];
			const Vector2& pos = tile.GetPosition();
			const int type = tile.GetType();

			SGE_Sprite& sprite = mSprites[type];
			sprite.SetPosition(pos + mOffset);
			sprite.Render();

			Rect bb = tile.GetBoundingBox();
			if (!tile.IsWalkable())
			{
				Graphics_DebugRect(bb + mOffset, 0x000000);
			}
			else
			{
				Graphics_DebugRect(bb + mOffset, 0x999999);
			}
		}
	}
}

Tile& Map::GetTile(int screenX, int screenY)
{
	const int x = (screenX - (int)mOffset.x) / mTileSize;
	const int y = (screenY - (int)mOffset.y) / mTileSize;
	const int index = x + (y * mColumns);
	return mTiles[index];
}

Tile& Map::GetTile(const Vector2& screenPos)
{
	int x = (int)screenPos.x;
	int y = (int)screenPos.y;
	return GetTile(x, y);
}

Tile& Map::GetTile(int index)
{
	return mTiles[index];
}

void Map::SetTileType(Tile& tile, int type)
{
	int newType = type % mSpriteCount;
	tile.SetType(newType);
	tile.SetWalkable(mTilePrototypes[newType].IsWalkable());
	tile.SetMovementCost(mTilePrototypes[newType].GetMovementCost());
	tile.SetDamage(mTilePrototypes[newType].GetDamage());
}

Rect Map::GetBoundingBoxFromSegment(const LineSegment& line) const
{
	// Validate the line segment
	if (line.from.x < 0.0f || line.from.x > GetWidth() ||
		line.from.y < 0.0f || line.from.y > GetHeight() ||
		line.to.x < 0.0f || line.to.x > GetWidth() ||
		line.to.y < 0.0f || line.to.y > GetHeight())
	{
		// Line segment is out of bound!
		return Rect();
	}
	
	// Convert position to indices
	const int fromX = static_cast<int>(line.from.x) / mTileSize;
	const int fromY = static_cast<int>(line.from.y) / mTileSize;
	const int toX = static_cast<int>(line.to.x) / mTileSize;
	const int toY = static_cast<int>(line.to.y) / mTileSize;

	// Calculate tile count
	const int countX = toX - fromX + 1;
	const int countY = toY - fromY + 1;
	
	// Get region
	Rect region;
	for (int y = 0; y < countY; ++y)
	{
		for (int x = 0; x < countX; ++x)
		{
			const int index = (fromX + x) + ((fromY + y) * mColumns);
			if (!mTiles[index].IsWalkable())
			{
				region += mTiles[index].GetBoundingBox();
			}
		}
	}
	return region;
}

Rect Map::GetIntersectingRegion(const Rect& bb) const
{
	if (bb.IsValid() == false)
	{
		return Rect();
	}

	const int fromX = static_cast<int>(bb.min.x) / mTileSize;
	const int fromY = static_cast<int>(bb.min.y) / mTileSize;
	const int toX = static_cast<int>(bb.max.x) / mTileSize;
	const int toY = static_cast<int>(bb.max.y) / mTileSize;

	// Calculate tile count
	const int countX = toX - fromX + 1;
	const int countY = toY - fromY + 1;

	Rect region;
	for (int y = 0; y < countY; ++y)
	{
		for (int x = 0; x < countX; ++x)
		{
			const int index = (fromX + x) + ((fromY + y) * mColumns);
			//if (!mTiles[index].IsWalkable())
			{
				region += mTiles[index].GetBoundingBox();
			}
		}
	}

	return region;
}

float Map::GetIntersectingAvgMovementCost(const Rect& bb) const
{
	if (bb.IsValid() == false)
	{
		return 1.0f;
	}

	const int fromX = static_cast<int>(bb.min.x) / mTileSize;
	const int fromY = static_cast<int>(bb.min.y) / mTileSize;
	const int toX = static_cast<int>(bb.max.x) / mTileSize;
	const int toY = static_cast<int>(bb.max.y) / mTileSize;

	// Calculate tile count
	const int countX = toX - fromX + 1;
	const int countY = toY - fromY + 1;

	// Add up the sum of the movement cost from all walkable intersecting tiles.
	int contributingTileCount = 0;
	float sumMovementCost = 0.0f;
	for (int y = 0; y < countY; ++y)
	{
		for (int x = 0; x < countX; ++x)
		{
			const int index = (fromX + x) + ((fromY + y) * mColumns);
			if (mTiles[index].IsWalkable())
			{
				sumMovementCost += static_cast<float>(mTiles[index].GetMovementCost());
				++contributingTileCount;
			}
		}
	}

	// Average the cost.
	float avgMovementCost = 0.0f;
	if (contributingTileCount > 0)
	{
		avgMovementCost = sumMovementCost / contributingTileCount;
	}

	// Always return at least 1 so the cost can be used as a dividend.
	if (avgMovementCost < 1.0f)
	{
		avgMovementCost = 1.0f;
	}
	
	return avgMovementCost;
}

int Map::IncrementTileType(int currentType)
{
	return (currentType + 1) % mSpriteCount;
}

int Map::DecrementTileType(int currentType)
{
	currentType--;
	if (currentType < 0)
	{
		currentType = mSpriteCount - 1;
	}
	return currentType;
}

void Map::StartPathfinding()
{
	mFlipNeighborOrder = false;
}

void Map::EndPathfinding()
{
}

void Map::GetTileNeighbors(int tileIndex, std::vector<int>& neighborsOut)
{
	neighborsOut.clear();

	const int maxIndex = mColumns * mRows;
	const int currentRow = tileIndex / mColumns;

	int leftIndex = tileIndex - 1;
	if (leftIndex / mColumns != currentRow)
	{
		leftIndex = -1;
	}

	int rightIndex = (tileIndex + 1);
	if (rightIndex >= maxIndex || rightIndex / mColumns != currentRow)
	{
		rightIndex = -1;
	}

	int topIndex = tileIndex - mColumns;
	if (topIndex < 0)
	{
		topIndex = -1;
	}
	int bottomIndex = tileIndex + mColumns;
	if (bottomIndex >= maxIndex)
	{
		bottomIndex = -1;
	}

	// Blocking tiles don't count.
	if (leftIndex != -1 && GetTile(leftIndex).IsWalkable() == false)
	{
		leftIndex = -1;
	}
	if (rightIndex != -1 && GetTile(rightIndex).IsWalkable() == false)
	{
		rightIndex = -1;
	}
	if (topIndex != -1 && GetTile(topIndex).IsWalkable() == false)
	{
		topIndex = -1;
	}
	if (bottomIndex != -1 && GetTile(bottomIndex).IsWalkable() == false)
	{
		bottomIndex = -1;
	}

	if (mFlipNeighborOrder == false)
	{
		neighborsOut.push_back(topIndex);
		neighborsOut.push_back(rightIndex);
		neighborsOut.push_back(bottomIndex);
		neighborsOut.push_back(leftIndex);
		mFlipNeighborOrder = true;
	}
	else
	{
		neighborsOut.push_back(topIndex);
		neighborsOut.push_back(leftIndex);
		neighborsOut.push_back(bottomIndex);
		neighborsOut.push_back(rightIndex);
		mFlipNeighborOrder = false;
	}
}

bool Map::LoadLevel(const char* pLevelFile)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pLevelFile, "r");

	// Read map dimensions
	fscanf_s(pFile, "%*s %d", &mColumns);
	fscanf_s(pFile, "%*s %d", &mRows);
	fscanf_s(pFile, "%*s %d", &mTileSize);
	fscanf_s(pFile, "%*s %d", &mTileCount);

	// Create tile prototype buffer
	mTilePrototypes = new Tile[mTileCount];

	// Create tile buffer
	mTiles = new Tile[mColumns * mRows];

	// Parse tile data
	do
	{
		char buffer[128];
		fscanf_s(pFile, "%s", buffer, 128);
		if(strcmp(buffer, "TileDefinition") == 0)
		{
			int type = 0;
			int collision = 0;
			int movementCost = 0;
			int damage = 0;
			fscanf_s(pFile, "%*s %d", &type);
			fscanf_s(pFile, "%*s %d", &collision);
			fscanf_s(pFile, "%*s %d", &movementCost);
			fscanf_s(pFile, "%*s %d", &damage);
			if(type >= 0 && type < mTileCount)
			{
				mTilePrototypes[type].SetWalkable(collision == 0);
				mTilePrototypes[type].SetMovementCost(movementCost);
				mTilePrototypes[type].SetDamage(damage);
			}
		}
		else
		{
			break;
		}
	} while(true);

	// Parse map data
	int tileType = 0;
	fgetc(pFile);	// Discard the newline
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = x + (y * mColumns);
			Tile& tile = mTiles[index];
			tile.mIndex = index;
			tile.SetPosition(Vector2((float)x * mTileSize, (float)y * mTileSize));
			tile.SetSize(mTileSize);
			fscanf_s(pFile, "%d", &tileType);
			tile.SetType(tileType);
			tile.SetWalkable(mTilePrototypes[tileType].IsWalkable());
			tile.SetMovementCost(mTilePrototypes[tileType].GetMovementCost());
			tile.SetDamage(mTilePrototypes[tileType].GetDamage());

			fgetc(pFile);	// Discard the comma or newline at the end of the line.
		}
	}

	// Close file
	fclose(pFile);
	pFile = nullptr;

	return true;
}

bool Map::LoadTexturePack(const char* pTexturePack)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pTexturePack, "r");

	// Get number of textures
	fscanf_s(pFile, "%*s %d", &mSpriteCount);

	// Make sure the sprite count is equal to the expected tile count for this map.
	if (mSpriteCount != mTileCount)
	{
		return false;
	}

	// Create sprite pool
	mSprites = new SGE_Sprite[mSpriteCount];

	// Load textures
	for (int i = 0; i < mSpriteCount; ++i)
	{
		char buffer[128];
		fscanf_s(pFile, "%s", buffer, 128);
		mSprites[i].Load(buffer);
	}

	// Close file
	fclose(pFile);
	pFile = nullptr;

	return true;
}
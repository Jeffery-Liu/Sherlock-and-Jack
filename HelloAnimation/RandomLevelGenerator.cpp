#include <iostream>
#include <fstream>
#include "RandomLevelGenerator.h"
using namespace std;

RandomLevelGenerator::RandomLevelGenerator()
	: mRandomNum(0)
{
}

RandomLevelGenerator::~RandomLevelGenerator()
{
}

void RandomLevelGenerator::GetRandomLevel()
{
	// ------------------------------------------- Assign 2D Array -------------------------------------------------------------------------
	AssignArray();

	// Spawn points Now only for p1 and p2
	SpawnPoints();

	// ---- Building sample 1 ---- Random position
	for (int i = 0; i < 5; i++)
	{
		while (isB1Created[i] != true)
		{
			CreateBuilding1(i);
		}
	}
	// ---- Building sample 2 ---- Random position
	for (int i = 0; i < 2; i++)
	{
		while (isB2Created[i] != true)
		{
			CreateBuilding2(i);
		}
	}

	// ---- Building sample 3 ---- Random position
	for (int i = 0; i < 2; i++)
	{
		while (isB3Created[i] != true)
		{
			CreateBuilding3(i);
		}
	}

	// ---- Trees ---- Random position
	for (int i = 0; i < 100; i++)
	{
		while (isTreeCreated[i] != true)
		{
			CreateTrees(i);
		}
	}

	GenerateLevelFile();


	
}

void RandomLevelGenerator::SpawnPoints()
{
	// ---- Spawn point for P1---- Fixed position
	int P1spX = 3, P1spY = 3;
	for (int x = P1spX - 1; x <= P1spX + 1; x++)
	{
		for (int y = P1spY - 1; y <= P1spY + 1; y++)
		{
			mArray[x][y] = 26;
		}
	}
	mArray[1][1] = 5;
	mArray[2][1] = 6;
	mArray[3][1] = 6;
	mArray[4][1] = 6;
	mArray[5][1] = 7;
	mArray[1][2] = 8;
	mArray[1][3] = 8;
	mArray[1][4] = 8;
	mArray[5][2] = 10;
	mArray[5][3] = 10;
	mArray[5][4] = 10;
	mArray[1][5] = 11;
	mArray[2][5] = 13;
	mArray[3][5] = 12;
	mArray[4][5] = 11;
	mArray[5][5] = 13;
	mArray[6][1] = 29;
	mArray[6][2] = 29;
	mArray[6][3] = 29;
	mArray[6][4] = 29;
	mArray[6][5] = 27;
	mArray[1][6] = 28;
	mArray[2][6] = 28;
	mArray[3][6] = 1;
	mArray[4][6] = 28;
	mArray[5][6] = 28;
	// Safe points
	mArray[3][6] = 33;
	mArray[7][1] = 33;
	mArray[7][2] = 33;
	mArray[7][3] = 33;
	mArray[7][4] = 33;
	mArray[7][5] = 33;
	mArray[7][6] = 33;
	mArray[1][7] = 33;
	mArray[2][7] = 33;
	mArray[3][7] = 33;
	mArray[4][7] = 33;
	mArray[5][7] = 33;
	mArray[6][7] = 33;

	// ---- Spawn point for P2---- Fixed position
	int P2spX = 37, P2spY = 22;
	mArray[37][22] = 26;
	mArray[39][20] = 22;
	mArray[39][21] = 22;
	mArray[39][22] = 22;
	mArray[39][23] = 22;
	mArray[39][24] = 22;
	mArray[39][24] = 22;
	mArray[38][24] = 22;
	mArray[37][24] = 22;
	mArray[36][24] = 24;
	mArray[35][24] = 22;
	mArray[38][23] = 22;
	mArray[38][22] = 23;
	mArray[38][21] = 22;
	mArray[38][20] = 22;
	mArray[37][23] = 22;
	mArray[37][21] = 25;
	mArray[37][20] = 25;
	mArray[36][23] = 22;
	mArray[36][22] = 25;
	mArray[36][21] = 22;
	mArray[36][20] = 22;
	mArray[35][23] = 22;
	mArray[35][22] = 25;
	mArray[35][21] = 22;
	mArray[35][20] = 22;
	mArray[34][23] = 20;
	mArray[34][21] = 20;
	mArray[34][20] = 20;
	mArray[34][19] = 20;
	mArray[38][19] = 20;
	mArray[36][19] = 20;
	mArray[35][19] = 20;
	// Safe points
	mArray[34][22] = 33;
	mArray[37][19] = 33;
	mArray[33][23] = 33;
	mArray[33][22] = 33;
	mArray[33][21] = 33;
	mArray[33][20] = 33;
	mArray[33][19] = 33;
	mArray[38][18] = 33;
	mArray[37][18] = 33;
	mArray[36][18] = 33;
	mArray[35][18] = 33;
	mArray[34][18] = 33;
}

// ------------------------------------------- Prefabs --------------------------------------------------------------------------------
// dust_brick.png			Type : 0		Collision : 1		MovementCost : 0
// dust_road.png			Type : 1		Collision : 0		MovementCost : 0
// dust_grass1.png			Type : 2		Collision : 0		MovementCost : 1
// dust_grass2.png			Type : 3		Collision : 0		MovementCost : 2
// dust_grass3.png			Type : 4		Collision : 0		MovementCost : 3
// dust_buildingA1.png		Type : 5		Collision : 1		MovementCost : 0
// dust_buildingA2.png		Type : 6		Collision : 1		MovementCost : 0
// dust_buildingA3.png		Type : 7		Collision : 1		MovementCost : 0
// dust_buildingA4.png		Type : 8		Collision : 1		MovementCost : 0
// dust_buildingA5.png		Type : 9		Collision : 1		MovementCost : 0
// dust_buildingA6.png		Type : 10		Collision : 1		MovementCost : 0
// dust_buildingA7.png		Type : 11		Collision : 1		MovementCost : 0
// dust_buildingA8.png		Type : 12		Collision : 0		MovementCost : 0
// dust_buildingA9.png		Type : 13		Collision : 1		MovementCost : 0
// dust_buildingB1.png		Type : 14		Collision : 1		MovementCost : 0
// dust_buildingB2.png		Type : 15		Collision : 1		MovementCost : 0
// dust_buildingB3.png		Type : 16		Collision : 1		MovementCost : 0
// dust_buildingB4.png		Type : 17		Collision : 1		MovementCost : 0
// dust_buildingB5.png		Type : 18		Collision : 0		MovementCost : 0
// dust_buildingB6.png		Type : 19		Collision : 1		MovementCost : 0
// dust_tree.png			Type : 20		Collision : 1		MovementCost : 0
// dust_roadblock.png		Type : 21		Collision : 0		MovementCost : 0
// dust_lake1.png			Type : 22		Collision : 1		MovementCost : 0
// dust_lake_ship.png		Type : 23		Collision : 1		MovementCost : 0
// dust_lake_vortex.png		Type : 24		Collision : 1		MovementCost : 0
// dust_bridge.png			Type : 25		Collision : 0		MovementCost : 0
// road.png					Type : 26		Collision : 0		MovementCost : 0
// dust_sign.png			Type : 27		Collision : 1		MovementCost : 0
// dust_roadblock.png		Type : 28		Collision : 1		MovementCost : 0
// dust_car.png				Type : 29		Collision : 1		MovementCost : 0
// dust_car2.png			Type : 30		Collision : 1		MovementCost : 0
// bomb.png					Type : 31		Collision : 0		MovementCost : 0

// map size = 40 * 25
// -|--------------> x
//  |
//  |
//  | 
//  y

void RandomLevelGenerator::CreateBuilding1(int num)
{
	int Building1X = rand() % 41, Building1Y = rand() % 26;
	int availableTileCounter = 0;
	for (int i = Building1X - 2; i <= Building1X + 2; i++)
	{
		for (int j = Building1Y - 2; j <= Building1Y + 2; j++)
		{
			if (mArray[i][j] == 1 || mArray[i][j] == 2 || mArray[i][j] == 3 || mArray[i][j] == 4)
			{
				availableTileCounter++;
			}
		}
	}
	if (availableTileCounter == 25)
	{
		mArray[Building1X - 1][Building1Y - 1] = 5;
		mArray[Building1X][Building1Y - 1] = 6;
		mArray[Building1X + 1][Building1Y - 1] = 7;
		mArray[Building1X - 1][Building1Y] = 8;
		mArray[Building1X][Building1Y] = 26;
		mArray[Building1X + 1][Building1Y] = 10;
		mArray[Building1X - 1][Building1Y + 1] = 11;
		mArray[Building1X][Building1Y + 1] = 12;
		mArray[Building1X + 1][Building1Y + 1] = 13;

		// safe points
		mArray[Building1X - 2][Building1Y - 2] = 33;
		mArray[Building1X - 1][Building1Y - 2] = 33;
		mArray[Building1X    ][Building1Y - 2] = 33;
		mArray[Building1X + 1][Building1Y - 2] = 33;
		mArray[Building1X + 2][Building1Y - 2] = 33;
		mArray[Building1X - 2][Building1Y + 2] = 33;
		mArray[Building1X - 1][Building1Y + 2] = 33;
		mArray[Building1X    ][Building1Y + 2] = 33;
		mArray[Building1X + 1][Building1Y + 2] = 33;
		mArray[Building1X + 2][Building1Y + 2] = 33;
		mArray[Building1X - 2][Building1Y - 1] = 33;
		mArray[Building1X - 2][Building1Y	 ] = 33;
		mArray[Building1X - 2][Building1Y + 1] = 33;
		mArray[Building1X + 2][Building1Y - 1] = 33;
		mArray[Building1X + 2][Building1Y	 ] = 33;
		mArray[Building1X + 2][Building1Y + 1] = 33;

		isB1Created[num] = true;
	}
	else
	{
		isB1Created[num] = false;
	}
}

void RandomLevelGenerator::CreateBuilding2(int num)
{
	int Building1X = rand() % 41, Building1Y = rand() % 26;
	int availableTileCounter = 0;
	for (int i = Building1X - 4; i <= Building1X + 3; i++)
	{
		for (int j = Building1Y - 2; j <= Building1Y + 2; j++)
		{
			if (mArray[i][j] == 1 || mArray[i][j] == 2 || mArray[i][j] == 3 || mArray[i][j] == 4)
			{
				availableTileCounter++;
			}
		}
	}
	if (availableTileCounter == 40)
	{
		mArray[Building1X - 3][Building1Y - 1] = 14;
		mArray[Building1X - 2][Building1Y - 1] = 15;
		mArray[Building1X - 1][Building1Y - 1] = 14;
		mArray[Building1X    ][Building1Y - 1] = 15;
		mArray[Building1X + 1][Building1Y - 1] = 14;
		mArray[Building1X + 2][Building1Y - 1] = 15;
		mArray[Building1X + 3][Building1Y - 1] = 1;

		mArray[Building1X - 3][Building1Y] = 16;
		mArray[Building1X - 2][Building1Y] = 17;
		mArray[Building1X - 1][Building1Y] = 16;
		mArray[Building1X    ][Building1Y] = 17;
		mArray[Building1X + 1][Building1Y] = 16;
		mArray[Building1X + 2][Building1Y] = 17;
		mArray[Building1X + 3][Building1Y] = 1;

		mArray[Building1X - 3][Building1Y + 1] = 18;
		mArray[Building1X - 2][Building1Y + 1] = 19;
		mArray[Building1X - 1][Building1Y + 1] = 19;
		mArray[Building1X	 ][Building1Y + 1] = 19;
		mArray[Building1X + 1][Building1Y + 1] = 19;
		mArray[Building1X + 2][Building1Y + 1] = 18;
		mArray[Building1X + 3][Building1Y + 1] = 27;

		// safe points
		mArray[Building1X - 4][Building1Y - 2] = 33;
		mArray[Building1X - 3][Building1Y - 2] = 33;
		mArray[Building1X - 2][Building1Y - 2] = 33;
		mArray[Building1X - 1][Building1Y - 2] = 33;
		mArray[Building1X - 0][Building1Y - 2] = 33;
		mArray[Building1X + 1][Building1Y - 2] = 33;
		mArray[Building1X + 2][Building1Y - 2] = 33;
		mArray[Building1X + 3][Building1Y - 2] = 33;
		mArray[Building1X - 4][Building1Y + 2] = 33;
		mArray[Building1X - 3][Building1Y + 2] = 33;
		mArray[Building1X - 2][Building1Y + 2] = 33;
		mArray[Building1X - 1][Building1Y + 2] = 33;
		mArray[Building1X - 0][Building1Y + 2] = 33;
		mArray[Building1X + 1][Building1Y + 2] = 33;
		mArray[Building1X + 2][Building1Y + 2] = 33;
		mArray[Building1X + 3][Building1Y + 2] = 33; 
		mArray[Building1X - 4][Building1Y - 1] = 33;
		mArray[Building1X - 4][Building1Y	 ] = 33;
		mArray[Building1X - 4][Building1Y + 1] = 33;
		mArray[Building1X + 3][Building1Y - 1] = 33;
		mArray[Building1X + 3][Building1Y	 ] = 33;

		isB2Created[num] = true;
	}
	else
	{
		isB2Created[num] = false;
	}
}

void RandomLevelGenerator::CreateBuilding3(int num)
{
	int Building1X = rand() % 41, Building1Y = rand() % 26;
	int availableTileCounter = 0;
	for (int i = Building1X - 3; i <= Building1X + 3; i++)
	{
		for (int j = Building1Y - 3; j <= Building1Y + 3; j++)
		{
			if (mArray[i][j] == 1 || mArray[i][j] == 2 || mArray[i][j] == 3 || mArray[i][j] == 4)
			{
				availableTileCounter++;
			}
		}
	}
	if (availableTileCounter == 49)
	{
		mArray[Building1X - 2][Building1Y - 2] = 5;
		mArray[Building1X - 1][Building1Y - 2] = 6;
		mArray[Building1X - 0][Building1Y - 2] = 6;
		mArray[Building1X + 1][Building1Y - 2] = 6;
		mArray[Building1X + 2][Building1Y - 2] = 7;

		mArray[Building1X - 2][Building1Y - 1] = 8;
		mArray[Building1X - 1][Building1Y - 1] = 26;
		mArray[Building1X - 0][Building1Y - 1] = 26;
		mArray[Building1X + 1][Building1Y - 1] = 26;
		mArray[Building1X + 2][Building1Y - 1] = 10;

		mArray[Building1X - 2][Building1Y] = 8;
		mArray[Building1X - 1][Building1Y] = 26;
		mArray[Building1X - 0][Building1Y] = 9;
		mArray[Building1X + 1][Building1Y] = 26;
		mArray[Building1X + 2][Building1Y] = 10;

		mArray[Building1X - 2][Building1Y + 1] = 8;
		mArray[Building1X - 1][Building1Y + 1] = 26;
		mArray[Building1X + 0][Building1Y + 1] = 26;
		mArray[Building1X + 1][Building1Y + 1] = 26;
		mArray[Building1X + 2][Building1Y + 1] = 10;

		mArray[Building1X - 2][Building1Y + 2] = 11;
		mArray[Building1X - 1][Building1Y + 2] = 13;
		mArray[Building1X - 0][Building1Y + 2] = 12;
		mArray[Building1X + 1][Building1Y + 2] = 11;
		mArray[Building1X + 2][Building1Y + 2] = 13;

		// safe points
		mArray[Building1X - 3][Building1Y - 3] = 33;
		mArray[Building1X - 3][Building1Y - 2] = 33;
		mArray[Building1X - 3][Building1Y - 1] = 33;
		mArray[Building1X - 3][Building1Y - 0] = 33;
		mArray[Building1X - 3][Building1Y + 1] = 33;
		mArray[Building1X - 3][Building1Y + 2] = 33;
		mArray[Building1X - 3][Building1Y + 3] = 33;
		mArray[Building1X + 3][Building1Y - 3] = 33;
		mArray[Building1X + 3][Building1Y - 2] = 33;
		mArray[Building1X + 3][Building1Y - 1] = 33;
		mArray[Building1X + 3][Building1Y - 0] = 33;
		mArray[Building1X + 3][Building1Y + 1] = 33;
		mArray[Building1X + 3][Building1Y + 2] = 33;
		mArray[Building1X + 3][Building1Y + 3] = 27;
		mArray[Building1X - 2][Building1Y - 3] = 33;
		mArray[Building1X - 1][Building1Y - 3] = 33;
		mArray[Building1X - 0][Building1Y - 3] = 33;
		mArray[Building1X + 1][Building1Y - 3] = 33;
		mArray[Building1X + 2][Building1Y - 3] = 33;
		mArray[Building1X - 2][Building1Y + 3] = 33;
		mArray[Building1X - 1][Building1Y + 3] = 33;
		mArray[Building1X - 0][Building1Y + 3] = 33;
		mArray[Building1X + 1][Building1Y + 3] = 33;
		mArray[Building1X + 2][Building1Y + 3] = 33;

		isB3Created[num] = true;
	}
	else
	{
		isB3Created[num] = false;
	}
}

void RandomLevelGenerator::CreateTrees(int num)
{
	int TreeX = rand() % 41, TreeY = rand() % 26;
	int availableTileCounter = 0;
	if (mArray[TreeX][TreeY] == 1 || mArray[TreeX][TreeY] == 2 || mArray[TreeX][TreeY] == 3 || mArray[TreeX][TreeY] == 4)
	{
		mArray[TreeX][TreeY] = 20;
		isTreeCreated[num] = true;
	}
	else
	{
		isTreeCreated[num] = false;
	}
}

void RandomLevelGenerator::GenerateLevelFile()
{
	srand(time(NULL));
	ofstream RandomLevel;
	RandomLevel.open("RandomLevelGenerator.txt");
	// Generate tile definition
	RandomLevel << "Columns: 40\nRows: 25\nTileSize: 32\nTileCount: 34\n\n";
	RandomLevel << "TileDefinition\nType: 0\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 1\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 2\nCollision: 0\nMovementCost: 1\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 3\nCollision: 0\nMovementCost: 2\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 4\nCollision: 0\nMovementCost: 3\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 5\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 6\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 7\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 8\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 9\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 10\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 11\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 12\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 13\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 14\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 15\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 16\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 17\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 18\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 19\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 20\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 21\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 22\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 23\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 24\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 25\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 26\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 27\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 28\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 29\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 30\nCollision: 1\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 31\nCollision: 0\nMovementCost: 5\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 32\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";
	RandomLevel << "TileDefinition\nType: 33\nCollision: 0\nMovementCost: 0\nDamage: 0\n\n";

	RandomLevel << "Map\n";

	// Generate level
	// Rows
	for (int row = 0; row < 25; row++)
	{
		// First Row, all tiles are walls
		if (row == 0)
		{
			for (int col = 0; col < 39; col++)
			{
				RandomLevel << '0' << mArray[col][row] << ',';
			}
			RandomLevel << '0' << mArray[39][row];
			RandomLevel << endl;
		}
		// Last Row, all tiles are walls
		else if (row == 24)
		{
			// Colums
			for (int col = 0; col < 39; col++)
			{
				RandomLevel << '0' << mArray[col][row] << ',';
			}
			RandomLevel << '0' << mArray[39][row];
		}
		else
		{
			// Columns
			for (int col = 0; col < 39; col++)
			{
				// First Column, all tiles are walls
				if (col == 0)
				{
					RandomLevel << '0' << mArray[col][row] << ',';
				}
				else
				{
					if (mArray[col][row] < 10)
					{
						RandomLevel << "0" << mArray[col][row] << ",";
					}
					else
					{
						RandomLevel << mArray[col][row] << ",";
					}
				}
			}
			// Last Column, all tiles are walls
			RandomLevel << '0' << mArray[39][row];
			RandomLevel << endl;
		}
	}
	RandomLevel.close();
}

void RandomLevelGenerator::AssignArray()
{
	// Rows
	for (int row = 0; row < 25; row++)
	{
		// First Row, all tiles are walls
		if (row == 0)
		{
			for (int col = 0; col < 39; col++)
			{
				mArray[col][row] = 0;
			}
			mArray[39][row] = 0;
		}
		// Last Row, all tiles are walls
		else if (row == 24)
		{
			// Colums
			for (int col = 0; col < 39; col++)
			{
				mArray[col][row] = 0;
			}
			mArray[39][row] = 0;
		}
		else
		{
			// Columns
			for (int col = 0; col < 39; col++)
			{
				// First Column, all tiles are walls
				if (col == 0)
				{
					mArray[col][row] = 0;
				}
				else
				{
					//mRandomNum = rand() % 30;
					//mArray[col][row] = mRandomNum;
					// 0-30
					//mArray[col][row] = rand() % 31; 
					mArray[col][row] = rand() % 4 + 1;

				}
			}
			// Last Column, all tiles are walls
			mArray[39][row] = 0;
		}
	}
}

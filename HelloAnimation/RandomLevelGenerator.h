#pragma once
#ifndef INCLUDED_RANDOMLEVELGENERATOR_H
#define INCLUDED_RANDOMLEVELGENERATOR_H

#include <SGE.h>
using namespace SGE;
#include "Tile.h"
#include <time.h>
using namespace std;

class RandomLevelGenerator
{
public:
	RandomLevelGenerator();
	~RandomLevelGenerator();

	void GetRandomLevel();
	void SpawnPoints();
	void CreateBuilding1(int num);
	void CreateBuilding2(int num);
	void CreateBuilding3(int num);
	void CreateTrees(int num);
	void GenerateLevelFile();
	void AssignArray();

private:
	int mRandomNum;
	int mArray[40][25] = {  };
	bool isB1Created[10] = { false };
	bool isB2Created[100] = { false };
	bool isB3Created[100] = { false };
	bool isTreeCreated[100] = { false };

};


#endif // #ifndef INCLUDED_RANDOMLEVELGENERATOR_H
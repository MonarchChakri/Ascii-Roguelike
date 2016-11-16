#pragma once
#include <vector>
#include <string>
#include <string>
#include "AsciiPlayer.h"
#include "AsciiEnemy.h"

using namespace std;

//The level stores the data for the level and the enemy list, and does a lot
//of the core game logic
class AsciiLevel
{
public:
	AsciiLevel();

	void loadAscii(string fileName, AsciiPlayer &player);
	void printAscii(AsciiPlayer _player);

	void movePlayerAscii(char input, AsciiPlayer &player);
	void updateEnemiesAscii(AsciiPlayer &player);

    //Getters
	char getTileAscii(int x, int y);
    //Setters
	void setTileAscii(int x, int y, char tile);
	void setNumPrintsAscii(int numPrints) { _numPrints = numPrints; }

private:
	void processPlayerMoveAscii(AsciiPlayer &player, int targetX, int targetY);
	void processEnemyMoveAscii(AsciiPlayer &player, int enemyIndex, int targetX, int targetY);
	void battleMonsterAscii(AsciiPlayer &player, int targetX, int targetY);

private:
    // I added this variable to keep track of how many lines we printed, so that we can pad
    // the bottom of the screen with newlines to keep the game board from jumping around!
    int _numPrints; 
    // Stores the level information
    vector <string> _levelData;
	vector <AsciiEnemy> _enemies;
};


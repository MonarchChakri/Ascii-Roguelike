#include "AsciiLevel.h"
#include <fstream>
#include <iostream>
#include <cstdio>

extern bool isDone;

//Constructor
AsciiLevel::AsciiLevel() {
    _numPrints = 0;
}

//This loads a level from the file fileName
void AsciiLevel::loadAscii(string fileName, AsciiPlayer &player) {

    //Loads the level
    ifstream file;

    //Open the file and quit if it fails to open
    file.open(fileName);
    if (file.fail()) {
        perror(fileName.c_str());
        system("PAUSE");
        exit(1);
    }

    string line;

    //Loop through the entire file, getting each row and
    //putting it in the line string.
    while (getline(file, line)) {
        //Push the current line onto the _levelData array
        _levelData.push_back(line);
    }

    //Close the file so we arent keeping open for longer than we need to
    file.close();

   
    char tile;

    //Loop through the game board and process the level
    for (int i = 0; i < _levelData.size(); i++) {
        //Loop through each letter in row i
        for (int j = 0; j < _levelData[i].size(); j++) {
            //This is the current tile we are looking at
            tile = _levelData[i][j];

            //Check the tile to see what we should do
			switch (tile) {
			case 'P': //Player
				player.setPositionAscii(j, i);
				break;
			case 'S': //Snake
				_enemies.push_back(AsciiEnemy("Snake", tile, 1, 3, 1, 10, 50));
				_enemies.back().setPositionAscii(j, i);
				break;
			case 'g': //Goblin
				_enemies.push_back(AsciiEnemy("Goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setPositionAscii(j, i);
				break;
			case 'O': //Ogre
				_enemies.push_back(AsciiEnemy("Ogre", tile, 4, 20, 40, 200, 500));
				_enemies.back().setPositionAscii(j, i);
				break;
			case 'D': //Dragon
				_enemies.push_back(AsciiEnemy("Dragon", tile, 100, 2000, 2000, 2000, 50000000));
				_enemies.back().setPositionAscii(j, i);
				break;
			case 'B': //Bandit
				_enemies.push_back(AsciiEnemy("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setPositionAscii(j, i);
				break;
			case '#': //All the tiles that dont need extra processing, in this case, walls and air
			case '.':
                //Doesnt need to do anthing, just break.
                break;
            default: //If we get here, that means we haven't registered the tile, so print out a warning
                printf("WARNING: Unknown tile %c at %d,%d", tile, j, i);
                system("Pause");
                break;
            }
        }
    }
    
}

//Prints out the level. TODO: print out the player stats to the right
void AsciiLevel::printAscii(AsciiPlayer _player) {

    //Trick for clearing the screen (kinda)
    printf("%s", string(100, '\n').c_str());

	//print Player Stats
	cout << "	Player Health		: " << _player.getPlayerHealthAscii() << endl;
	cout << "	Player Level		: " << _player.getPlayerLevelAscii() << endl;
	cout << "	Player Attack		: " << _player.getPlayerAttackAscii() << endl;
	cout << "	Player Defence		: " << _player.getPlayerDefenceAscii() << endl;
	cout << "	Player Experience	: " << _player.getPlayerExperienceAscii() << endl;

	//could have also used
    //cout << string(100, '\n');
    //but printf is typically faster

    for (int i = 0; i < _levelData.size(); i++) {
        printf("%s\n", _levelData[i].c_str());
    }

    //This pads the bottom with extra newlines based on how many extra lines
    //have been printed. So for instance, when the player is battling something, 
    //the game board doesnt jump around
    if (_numPrints < 5){
        printf("%s", string(5 - _numPrints, '\n').c_str());
    }

    //Set numPrints to zero each time we reprint the screen
    _numPrints = 0;

}

//Moves the player based on his
void AsciiLevel::movePlayerAscii(char input, AsciiPlayer &player) {

    int playerX;
    int playerY;

    //Get the position from the player using the reference parameters playerX and playerY
	player.getPositionAscii(playerX, playerY);

    //Process the input
    switch (input) {

    case 'w': //up
    case 'W':
		processPlayerMoveAscii(player, playerX, playerY - 1);
        break;
    case 's': //down
    case 'S':
		processPlayerMoveAscii(player, playerX, playerY + 1);
        break;
    case 'a': //left
    case 'A':
		processPlayerMoveAscii(player, playerX - 1, playerY);
        break;
    case 'd': //right
    case 'D':
		processPlayerMoveAscii(player, playerX + 1, playerY);
        break;
    default: //If he entered anything else, invalid input!
        _numPrints+=2; // We are about to print 2 extra lines
		printAscii(player); //reprint the board
        printf("INVALID INPUT!\n");
        system("PAUSE");
        break;
    }

}

//Updates all the enemy AI
void AsciiLevel::updateEnemiesAscii(AsciiPlayer &player) {
    char aiMove;
    int playerX;
    int playerY;
    int enemyX;
    int enemyY;
    
    //Get player position
	player.getPositionAscii(playerX, playerY);

    //Loop through the enemies vector
    for (int i = 0; i < _enemies.size(); i++) {
        //Get the AI movement from the enemy
		aiMove = _enemies[i].getMoveAscii(playerX, playerY);
        //Get the current enemy position
		_enemies[i].getPositionAscii(enemyX, enemyY);
        //Process the AI move command
        switch (aiMove) {

        case 'w': //up
			processEnemyMoveAscii(player, i, enemyX, enemyY - 1);
            break;
        case 's': //down
			processEnemyMoveAscii(player, i, enemyX, enemyY + 1);
            break;
        case 'a': //left
			processEnemyMoveAscii(player, i, enemyX - 1, enemyY);
            break;
        case 'd': //right
			processEnemyMoveAscii(player, i, enemyX + 1, enemyY);
            break;
        }
    }
}

//Gets a tile from the board
char AsciiLevel::getTileAscii(int x, int y) {
    return _levelData[y][x];
}

//sets a tile on the board
void AsciiLevel::setTileAscii(int x, int y, char tile) {
    _levelData[y][x] = tile;
}

//Process the players movement
void AsciiLevel::processPlayerMoveAscii(AsciiPlayer &player, int targetX, int targetY) {
    int playerX;
    int playerY;
	player.getPositionAscii(playerX, playerY);
    
    //Get the tile that the player wants to move onto
	char moveTile = getTileAscii(targetX, targetY);

    //Process the tile
    switch (moveTile) {
    case '.': //If its a dot, we can move!
		player.setPositionAscii(targetX, targetY);
		setTileAscii(playerX, playerY, '.');
		setTileAscii(targetX, targetY, 'P');
        break;
        //You should add other things like shops and doors in here!
    case '#': //if its a wall, we break!
        break;
    default: //If its anything else, its an enemy, so battle!
		battleMonsterAscii(player, targetX, targetY);
        break;
    }
}
//Process an enemy movement
void AsciiLevel::processEnemyMoveAscii(AsciiPlayer &player, int enemyIndex, int targetX, int targetY) {

    int enemyX;
    int enemyY;

	_enemies[enemyIndex].getPositionAscii(enemyX, enemyY);

    //Get the tile the enemy wants to move to
	char moveTile = getTileAscii(targetX, targetY);

    //Process the tile
    switch (moveTile) {
    case '.': //if its a dot, we move there
		_enemies[enemyIndex].setPositionAscii(targetX, targetY);
		setTileAscii(enemyX, enemyY, '.');
		setTileAscii(targetX, targetY, _enemies[enemyIndex].getTileAscii());
        break;
	case 'P': //If its the player, we battle!
		battleMonsterAscii(player, enemyX, enemyY);
        break;
    default:
        break;
    }
}

//Simulates a round of combat between the player and the monster at targetX,targetY
void AsciiLevel::battleMonsterAscii(AsciiPlayer &player, int targetX, int targetY) {

    int enemyX;
    int enemyY;
    int playerX;
    int playerY;
    int attackRoll;
    int attackResult;
    string enemyName;

	player.getPositionAscii(playerX, playerY);

    //Loop through all the enemies so we can find the enemy we are currently fighting
    for (int i = 0; i < _enemies.size(); i++) {

		_enemies[i].getPositionAscii(enemyX, enemyY);

        //If the enemy coordinates are the same as the target coordinates, we have a match!
        if (targetX == enemyX && targetY == enemyY) {

            //Get the name of the enemy
			enemyName = _enemies[i].getNameAscii();

            _numPrints += 2; // We are about to print 2 extra lines
			printAscii(player); //reprint the board

            //*** Player Turn ***
			attackRoll = player.attackAscii();
            printf("\nPlayer attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);
			attackResult = _enemies[i].takeDamageAscii(attackRoll);

            //If attack result is not zero, then the monster died
            if (attackResult != 0) {
				setTileAscii(targetX, targetY, '.');
                _numPrints += 2; // We are about to print 2 extra lines
				printAscii(player); //reprint the board
                printf("Monster died!\n");

                //remove the enemy
                _enemies[i] = _enemies.back();
                _enemies.pop_back();
                i--;

                system("PAUSE");
				player.addExperienceAscii(attackResult);
                
                return;
            }

            system("PAUSE");

            _numPrints += 2; // We are about to print 2 extra lines
			printAscii(player); //reprint the board
            
            //*** Enemy turn ***
			attackRoll = _enemies[i].attackAscii();
            printf("%s attacked player with a roll of %d\n", enemyName.c_str(), attackRoll);

			attackResult = player.takeDamageAscii(attackRoll);

            //If attack result is not zero, the player died
            if (attackResult != 0) {
				setTileAscii(playerX, playerY, 'x');
				printAscii(player);
                printf("You Died!!\n");
				isDone = true;
            }
        }
    }
}
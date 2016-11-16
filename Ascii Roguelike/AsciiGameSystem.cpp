#include "AsciiPlayer.h"
#include "AsciiGameSystem.h"
#include <iostream>
#include <conio.h>

bool isDone = false;

//Constructor sets up the game
AsciiGameSystem::AsciiGameSystem(string levelFileName){
    
    //Initialize the player properties. TODO: Load and save from a save file
	_player.initAscii(1, 100, 10, 10, 0);

    //Load the level from file
	_level.loadAscii(levelFileName, _player);
  
    printf("%s was loaded!\n", levelFileName.c_str());
    printf("\n*Be sure to make your console window bigger for the best experience.\n\n");
    system("PAUSE");
} 

void AsciiGameSystem::playGameAscii() {
	isDone = false;
    while (isDone != true) {
        //playerMove prints "Enter a move command" so we tell the level about it so it can format
		_level.setNumPrintsAscii(1);
        //print the board
		_level.printAscii(_player);
        //get player input
		playerMoveAscii();
        //update level AI
		_level.updateEnemiesAscii(_player);
    }
}

//Player input
void AsciiGameSystem::playerMoveAscii() {
	//Moves player
    char input;
	system("Color e");
    printf("Enter a move command (w/s/a/d): ");
    input = _getch();
	_level.movePlayerAscii(input, _player);

}
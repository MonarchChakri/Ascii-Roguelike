#pragma once
#include <string>

using namespace std;

class AsciiEnemy
{
public:
    //Constructor
	AsciiEnemy(string name, char tile, int level, int attack, int defense, int health, int xp);

    //Setters
	void setPositionAscii(int x, int y);

    //Getters
	void getPositionAscii(int &x, int &y);
	string getNameAscii() { return _name; }
	char getTileAscii() { return _tile; }

	int attackAscii();
	int takeDamageAscii(int attack);

    //Gets AI move command
	char getMoveAscii(int playerX, int playerY);

private:
    string _name;
    char _tile;

    //Properties
    int _level;
    int _attack;
    int _defense;
    int _health;
    int _experienceValue;

    //Position
    int _x;
    int _y;
};


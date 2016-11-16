#pragma once

class AsciiPlayer
{
public:
	AsciiPlayer();
	void initAscii(int level, int health, int attack, int defense, int experience);

	int attackAscii();
	int takeDamageAscii(int attack);

	//Setters
	void setPositionAscii(int x, int y);

	void addExperienceAscii(int experience);

	//Getters
	void getPositionAscii(int &x, int &y);

	int getPlayerHealthAscii(){ return _health; }
	int getPlayerLevelAscii(){ return _level; }
	int getPlayerAttackAscii(){ return _attack; }
	int getPlayerDefenceAscii(){ return _defense; }
	int getPlayerExperienceAscii(){ return _experience; }

private:
    //Properties
    int _level;
    int _health;
    int _attack;
    int _defense;
    int _experience;

    //Position
    int _x;
    int _y;
};


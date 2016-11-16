#include "AsciiPlayer.h"
#include <random>
#include <ctime>

using namespace std;

//Constructor, just initializes position to zero
AsciiPlayer::AsciiPlayer() {
    _x = 0;
    _y = 0;
}

//Initializes the player with properties
void AsciiPlayer::initAscii(int level, int health, int attack, int defense, int experience) {
    _level = level;
    _health = health;
    _attack = attack;
    _defense = defense;
    _experience = experience;
}

int AsciiPlayer::attackAscii() {
    static default_random_engine randomEngine(time(NULL));
    uniform_int_distribution<int> attackRoll(1, _attack);
    return attackRoll(randomEngine);
}

//Sets the position of the player
void AsciiPlayer::setPositionAscii(int x, int y) {
    _x = x;
    _y = y;
}

void AsciiPlayer::addExperienceAscii(int experience) {
    _experience += experience;
    //Level Up!
    while (_experience > 50) {
        printf("Leveled up!\n");
		_experience -= 50;
		_attack += 10;
		_defense += 50;
		_health += 10;
		_level++;
        system("PAUSE");
    }

}

//Gets the position of the player using reference variables
void AsciiPlayer::getPositionAscii(int &x, int &y) {
    x = _x;
    y = _y;
}

//Take damage from an attack. Returns 1 if he died, 0 otherwise
int AsciiPlayer::takeDamageAscii(int attack) {
    _defense -= attack;
	system("color c");
	system("PAUSE");
	//check if the attack does damage
    if (attack > 0) {
		_health -= attack;
        //check if he died
        if (_health <= 0) return 1;
    }
    return 0;
}
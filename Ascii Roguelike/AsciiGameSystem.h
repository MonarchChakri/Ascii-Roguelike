#pragma once
#include "AsciiPlayer.h"
#include "AsciiLevel.h"
#include <string>

using namespace std;

class AsciiGameSystem
{
public:
	AsciiGameSystem(string levelFileName);
	void playGameAscii();
	void playerMoveAscii();

private:
	AsciiPlayer _player;
	AsciiLevel _level;
};


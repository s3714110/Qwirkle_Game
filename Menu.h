#pragma once
#include "Game.h"

class Menu {
private:

public:
	Menu();
	~Menu();

	void run();

	Game* newGame();
	Game* loadGame();
};
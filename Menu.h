#ifndef _MENU_
#define _MENU_

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
#endif
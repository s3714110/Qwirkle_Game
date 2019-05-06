#pragma once
#include "Tile.h"
#include "LinkedList.h"


// Game creates and destroys the tiles that are used in the game.
// it will pass the reference for these tiles to all other classes.
// no other classes should delete the tiles they use (only stop referencing them)
// tiles are destroyed in the Game destructor
class Game {
private:
	LinkedList* tiles;

	void init_tiles();

public:
	Game();
	~Game();

	LinkedList* getTiles();
};
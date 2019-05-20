#pragma once
#include "Tile.h"
#include "LinkedList.h"
#include "Board.h"
#include "Player.h"
#include "TileBag.h"

// Game creates and destroys the tiles that are used in the game.
// it will pass the reference for these tiles to all other classes.
// no other classes should delete the tiles they use (only stop referencing them)
// tiles are destroyed in the Game destructor
class Game {
private:
	LinkedList* tiles;
	Board* board;
	Player** players;
	TileBag* tilebag;
	int playerCount;
	LinkedList* init_tiles();
	void fillPlayerHand(Player* player);
	void init_playerhand();

public:
	Game(Board* board, Player** players, int playerCount);
	~Game();
	void run();
	LinkedList* getTiles();
	Tile* getTile(std::string tileString);
	bool replace(Player* player, Tile* tile);
	bool place(Player* player, Tile* tile, int row, int col);
	void playerMove(Player* player);

};

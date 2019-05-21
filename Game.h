#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Player.h"
#include "TileBag.h"

static const std::map<std::string, int> rowStringToIntMap = {
  { "A", 0 },
  { "B", 1 },
  { "C", 2 },
  { "D", 3 },
  { "E", 4 },
  { "F", 5 },
  { "G", 6 },
  { "H", 7 },
  { "I", 8 },
  { "J", 9 },
  { "K", 10 },
  { "L", 11 },
  { "M", 12 },
  { "N", 13 },
  { "O", 14 },
  { "P", 15 },
  { "Q", 16 },
  { "R",17 },
  { "S", 18 },
  { "T", 19 },
  { "U", 20 },
  { "V", 21 },
  { "W", 22 },
  { "X", 23 },
  { "Y", 24 },
  { "Z", 25 }
};

// Game creates and destroys the tiles that are used in the game.
// it will pass the reference for these tiles to all other classes.
// no other classes should delete the tiles they use (only stop referencing them)
// tiles are destroyed in the Game destructor
class Game {
private:
	LinkedList* tiles;
	Board* board;
	Player** players;
	int playerTurn;
	TileBag* tilebag;
	int playerCount;
	LinkedList* init_tiles();
	void fillPlayerHand(Player* player);
	void init_playerhand();

public:
	Game(Board* board, Player** players, int playerCount);
	Game(Board* board, Player** players, int playerCount, TileBag* tilebag, int playerTurn);
	~Game();
	void run();

	LinkedList* getTiles();
	Tile* getTile(std::string tileString);
	bool replace(Player* player, Tile* tile);
	bool place(Tile* tile, int row, int col);
	void playerMove(Player* player);

};
#endif
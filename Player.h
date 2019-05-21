#ifndef _PLAYER_
#define _PLAYER_

#include <string>

#include "LinkedList.h"


class Player {
private:
	std::string id;
	std::string name;
	int score;
	LinkedList* hand;

public:
	Player(std::string id, std::string name);
	std::string getName();
	int getScore();
	int tilesInHand();
	void addToScore(int points);
	void addToHand(Tile* tile);
	void removeFromHand(Tile* tile);
	bool hasTile(Tile* tile);
	LinkedList* getPlayerHand();
};
#endif
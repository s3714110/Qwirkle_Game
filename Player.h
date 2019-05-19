#pragma once
#include <string>

#include "Tile.h"
#include "LinkedList.h"

typedef LinkedList* PlayerHand;

class Player {
private:
	std::string id;
	std::string name;
	int score;
	PlayerHand hand;

public:
	Player(std::string id, std::string name);
	std::string getName();
	int getScore();
	int tilesInHand();
	void addToScore(int points);
	void addToHand(Tile* tile);
	void removeFromHand(Tile* tile);
	PlayerHand getPlayerHand();
	bool playerHasTile(Tile* tile);
};

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
	PlayerHand playerhand;

public:
	Player(std::string id, std::string name);
};
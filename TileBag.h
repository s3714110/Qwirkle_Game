#pragma once
#include "Tile.h"
#include "LinkedList.h"

#define NUM_UNIQUE_TILES 2

class TileBag {
private:
	//LinkedList* tiles;
	LinkedList* shuffledList;
	int amountTiles;

public:

	TileBag(LinkedList* tiles);
	Tile* removeFromBag();
	void addToBag(Tile* tile);
	LinkedList* shuffleBag(LinkedList* unshuffledList);
	int amountTilesLeft();
};

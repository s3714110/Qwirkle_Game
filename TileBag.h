#pragma once
#include "Tile.h"
#include "LinkedList.h"

#define NUM_UNIQUIE_TILES 2

class TileBag {
private:
	//LinkedList* tiles;
	LinkedList* unshuffledList;
	LinkedList* shuffledList;

public:

	TileBag(LinkedList* tiles);
	Tile* removeFromBag();
	void addToBag(Tile* tile);
};

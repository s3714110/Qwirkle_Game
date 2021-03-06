#ifndef _TILE_BAG_
#define _TILE_BAG_

#include "LinkedList.h"

#define NUM_UNIQUE_TILES 2

class TileBag {
private:
	LinkedList* shuffledList;
	int amountTiles;

public:
	TileBag(LinkedList* tiles);
	~TileBag();
	Tile* removeFromBag();
	void addToBag(Tile* tile);
	LinkedList* shuffleBag(LinkedList* unshuffledList);
	int amountTilesLeft();
	LinkedList* getTiles();
};
#endif

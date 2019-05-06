#pragma once
#include "Tile.h"
#include "LinkedList.h"

class TileBag {
private:
	LinkedList* tiles;

public:
	TileBag(LinkedList* tiles);
};
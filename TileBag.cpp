#include "TileBag.h"
#include <random>

TileBag::TileBag(LinkedList* tiles) {
	unshuffledList = new LinkedList();
	shuffledList = new LinkedList();

	// Make an unshuffled list with the requested amount of copies of
	//  each tile
	for(int i=0;i< NUM_UNIQUIE_TILES;i++){
		for(int j=0;j<tiles->size();j++){
			unshuffledList->add(tiles->get(j));
		}
	}

	// Initialisation for random number generator based on internal
	//  clock
	std::random_device engine;

	// Add tiles to the shuffled list from the unshuffled list
	int amountTiles = unshuffledList->size();
	for(int i=0;i<amountTiles;i++){
		std::uniform_int_distribution<int> uniform_dist(1, unshuffledList->size());
		int index = uniform_dist(engine);
		shuffledList->add(unshuffledList->get(index));
		unshuffledList->remove(index);
	}
	shuffledList->get(1);
}

Tile* TileBag::removeFromBag(){
	Tile* tile = shuffledList->get(1);
	shuffledList->removeHead();
	return tile;
}

void TileBag::addToBag(Tile* tile){
	shuffledList->addTail(tile);
}

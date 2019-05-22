#include "TileBag.h"
#include <random>

TileBag::TileBag(LinkedList* tiles) {
	shuffledList = tiles;
	amountTiles = shuffledList->size();

	if (tiles->size() > 0) {
		shuffledList = shuffleBag(shuffledList);
	}
}
TileBag::~TileBag() {
	delete shuffledList;
}
Tile* TileBag::removeFromBag(){
	Tile* tile = shuffledList->get(1);
	shuffledList->removeHead();
	return tile;
}

void TileBag::addToBag(Tile* tile){
	shuffledList->addTail(tile);
	amountTiles++;
}

LinkedList* TileBag::shuffleBag(LinkedList* unshuffledList){

	shuffledList = new LinkedList();

	// Initialisation for random number generator based on internal
	//  clock
	std::random_device engine;

	// Add tiles to the shuffled list from the unshuffled list
	amountTiles = unshuffledList->size();
	for(int i=0;i<amountTiles;i++){
		std::uniform_int_distribution<int> uniform_dist(0, unshuffledList->size()-1);
		int index = uniform_dist(engine);
		shuffledList->add(unshuffledList->get(index));
		unshuffledList->remove(index);
	}

	delete unshuffledList;

	return shuffledList;
}

int TileBag::amountTilesLeft(){
	return shuffledList->size();
}

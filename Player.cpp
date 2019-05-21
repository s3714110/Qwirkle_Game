#include "Player.h"


Player::Player(std::string id, std::string name) {
	this->id = id;
	this->name = name;
	score = 0;
	hand = new LinkedList();
}

std::string Player::getName(){
	return this->name;
}

int Player::getScore(){
	return this->score;
}
void Player::addToScore(int points) {
	score += points;
}
void Player::addToHand(Tile* tile){
	hand->addTail(tile);
}

void Player::removeFromHand(Tile* tile) {
	hand->remove(tile);
}

bool Player::hasTile(Tile* tile) {
	return hand->contains(tile);
}

LinkedList* Player::getPlayerHand(){
	return hand;
}

int Player::tilesInHand(){
	return hand->size();
}


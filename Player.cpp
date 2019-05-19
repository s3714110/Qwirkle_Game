#include "Player.h"


Player::Player(std::string id, std::string name) {
	this->id = id;
	this->name = name;
	this->hand = hand;
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

PlayerHand Player::getPlayerHand(){
	return hand;
}

bool Player::playerHasTile(Tile* tile) {
	bool status = false;

	for (int i = 0; i < hand->size(); i++) {
		if (tile->equal(hand->get(i))) {
			status = true;
		}
	}

	return status;
}



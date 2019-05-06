#include "Player.h"

Player::Player(std::string id, std::string name) {
	Player::id = id;
	Player::name = name;
	score = 0;
	playerhand = new LinkedList();
}
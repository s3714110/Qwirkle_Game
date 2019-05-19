#include "Game.h"
#include "qwirkle_io.h"
#include <iostream>

LinkedList* Game::init_tiles() {
	LinkedList* _tiles = new LinkedList();

	_tiles->add(new Tile(COLOR::RED, SHAPE::CIRCLE));
	_tiles->add(new Tile(COLOR::RED, SHAPE::FOUR_STAR));
	_tiles->add(new Tile(COLOR::RED, SHAPE::DIAMOND));
	_tiles->add(new Tile(COLOR::RED, SHAPE::SQUARE));
	_tiles->add(new Tile(COLOR::RED, SHAPE::SIX_STAR));
	_tiles->add(new Tile(COLOR::RED, SHAPE::CLOVER));

	_tiles->add(new Tile(COLOR::ORANGE, SHAPE::CIRCLE));
	_tiles->add(new Tile(COLOR::ORANGE, SHAPE::FOUR_STAR));
	_tiles->add(new Tile(COLOR::ORANGE, SHAPE::DIAMOND));
	_tiles->add(new Tile(COLOR::ORANGE, SHAPE::SQUARE));
	_tiles->add(new Tile(COLOR::ORANGE, SHAPE::SIX_STAR));
	_tiles->add(new Tile(COLOR::ORANGE, SHAPE::CLOVER));

	_tiles->add(new Tile(COLOR::YELLOW, SHAPE::CIRCLE));
	_tiles->add(new Tile(COLOR::YELLOW, SHAPE::FOUR_STAR));
	_tiles->add(new Tile(COLOR::YELLOW, SHAPE::DIAMOND));
	_tiles->add(new Tile(COLOR::YELLOW, SHAPE::SQUARE));
	_tiles->add(new Tile(COLOR::YELLOW, SHAPE::SIX_STAR));
	_tiles->add(new Tile(COLOR::YELLOW, SHAPE::CLOVER));

	_tiles->add(new Tile(COLOR::GREEN, SHAPE::CIRCLE));
	_tiles->add(new Tile(COLOR::GREEN, SHAPE::FOUR_STAR));
	_tiles->add(new Tile(COLOR::GREEN, SHAPE::DIAMOND));
	_tiles->add(new Tile(COLOR::GREEN, SHAPE::SQUARE));
	_tiles->add(new Tile(COLOR::GREEN, SHAPE::SIX_STAR));
	_tiles->add(new Tile(COLOR::GREEN, SHAPE::CLOVER));

	_tiles->add(new Tile(COLOR::BLUE, SHAPE::CIRCLE));
	_tiles->add(new Tile(COLOR::BLUE, SHAPE::FOUR_STAR));
	_tiles->add(new Tile(COLOR::BLUE, SHAPE::DIAMOND));
	_tiles->add(new Tile(COLOR::BLUE, SHAPE::SQUARE));
	_tiles->add(new Tile(COLOR::BLUE, SHAPE::SIX_STAR));
	_tiles->add(new Tile(COLOR::BLUE, SHAPE::CLOVER));

	_tiles->add(new Tile(COLOR::PURPLE, SHAPE::CIRCLE));
	_tiles->add(new Tile(COLOR::PURPLE, SHAPE::FOUR_STAR));
	_tiles->add(new Tile(COLOR::PURPLE, SHAPE::DIAMOND));
	_tiles->add(new Tile(COLOR::PURPLE, SHAPE::SQUARE));
	_tiles->add(new Tile(COLOR::PURPLE, SHAPE::SIX_STAR));
	_tiles->add(new Tile(COLOR::PURPLE, SHAPE::CLOVER));

	return _tiles;
}

void Game::init_playerhand() {
	// For each player, initialise their hands with 6 tiles each
	for (int i = 0; i < playerCount; i++) {
		for (int j = 0; j < 6; j++) {
			Tile* tile = tilebag->removeFromBag();
			players[i]->addToHand(tile);
		}
	}
}

Game::Game(Board* board, Player** players, int playerCount) {

	// Random number generator
	int min = 1;
	int max = 36;

	tiles = init_tiles();
	init_tiles();
	// Creates a tile bag full of random tiles
	tilebag = new TileBag(tiles);

	this->board = board;
	this->players = players;
	this->playerCount = playerCount;

	// Initialise Player hands
	init_playerhand();
}
Game::~Game() {

	for (int i = 0; i < tiles->size(); i++) {
		delete tiles->get(i);
	}

	for (int i = 0; i < playerCount; i++) {
		delete players[i];
	}

	delete tiles;
	delete players;
	delete tilebag;
	delete board;
}

LinkedList* Game::getTiles() {
	return tiles;
}

Tile* Game::getTile(std::string tileString) {
	Tile* tile = nullptr;
	
	Tile* searchTile = nullptr;
	for (int i = 0; i < tiles->size(); i++) {
		searchTile = tiles->get(i);
		
		if ( 0 == tileString.compare(searchTile->toString())) {
			tile = searchTile;
			break;
		}
	}

	return tile;
}

// Game play starts
void Game::run() {
	bool endgame = false;
	Player* currentPlayer = nullptr;
	int playersTurn = 0;


	while (endgame == false) {
		currentPlayer = players[playersTurn];

		// Get the current players hands
		LinkedList* hand = currentPlayer->getPlayerHand();


		displayMessage(currentPlayer->getName() + ", its your turn!\n");
		displayScoreBoard(players, playerCount);
		displayBoard(board);
		displayPlayerHand(currentPlayer);


		while (!playerMove(currentPlayer)) {
			displayMessage("\nInvalid Move\n");
		}

		playersTurn++;
		if (playersTurn > playerCount - 1) {
			playersTurn = 0;
		}
	}
}

bool Game::playerMove(Player* player) {
	bool status = false;

	std::vector<std::string> move = getPlayerMove();

	// invalid entry
	if (move.size() == 0) {
		return status;
	}

	// player doesnt have tile return
	Tile* tile = getTile(move.at(0));
	if (!player->playerHasTile(tile)) {
		return status;
	}


	// Passed all checks

	// Do Replace
	if (move.size() == 1) {
		if (replace(player, tile)) {
			status = true;
		}
	}
	// Do Place (Need a better what of converting user input into row/col value)
	else if (move.size() == 2) {
		std::string _row_ = move.at(1).substr(0, 1);
		std::string _col_ = move.at(1).substr(1);

		int row = rows.find(_row_)->second;
		int col = std::stoi(_col_);
		if (place(player, tile, row, col)) {
			status = true;
		}
	}


	return status;
}

bool Game::replace(Player* player, Tile* tile) {
	bool status = false;

	player->removeFromHand(tile);
	Tile* newTile = tilebag->removeFromBag();
	player->addToHand(newTile);
	status = true;

	return status;
}

bool Game::place(Player* player, Tile* tile, int row, int col) {
	bool status = false;

	int points = 0;

	if (board->placeTile(tile, row, col, points)) {
		player->removeFromHand(tile);
		player->addToScore(points);
		status = true;
	}

	return status;
}








#include "Game.h"

void Game::init_tiles() {
	tiles = new LinkedList();


	tiles->add(new Tile(COLOR::RED, SHAPE::CIRCLE));
	tiles->add(new Tile(COLOR::RED, SHAPE::FOUR_STAR));
	tiles->add(new Tile(COLOR::RED, SHAPE::DIAMOND));
	tiles->add(new Tile(COLOR::RED, SHAPE::SQUARE));
	tiles->add(new Tile(COLOR::RED, SHAPE::SIX_STAR));
	tiles->add(new Tile(COLOR::RED, SHAPE::CLOVER));

	tiles->add(new Tile(COLOR::ORANGE, SHAPE::CIRCLE));
	tiles->add(new Tile(COLOR::ORANGE, SHAPE::FOUR_STAR));
	tiles->add(new Tile(COLOR::ORANGE, SHAPE::DIAMOND));
	tiles->add(new Tile(COLOR::ORANGE, SHAPE::SQUARE));
	tiles->add(new Tile(COLOR::ORANGE, SHAPE::SIX_STAR));
	tiles->add(new Tile(COLOR::ORANGE, SHAPE::CLOVER));

	tiles->add(new Tile(COLOR::YELLOW, SHAPE::CIRCLE));
	tiles->add(new Tile(COLOR::YELLOW, SHAPE::FOUR_STAR));
	tiles->add(new Tile(COLOR::YELLOW, SHAPE::DIAMOND));
	tiles->add(new Tile(COLOR::YELLOW, SHAPE::SQUARE));
	tiles->add(new Tile(COLOR::YELLOW, SHAPE::SIX_STAR));
	tiles->add(new Tile(COLOR::YELLOW, SHAPE::CLOVER));

	tiles->add(new Tile(COLOR::GREEN, SHAPE::CIRCLE));
	tiles->add(new Tile(COLOR::GREEN, SHAPE::FOUR_STAR));
	tiles->add(new Tile(COLOR::GREEN, SHAPE::DIAMOND));
	tiles->add(new Tile(COLOR::GREEN, SHAPE::SQUARE));
	tiles->add(new Tile(COLOR::GREEN, SHAPE::SIX_STAR));
	tiles->add(new Tile(COLOR::GREEN, SHAPE::CLOVER));

	tiles->add(new Tile(COLOR::BLUE, SHAPE::CIRCLE));
	tiles->add(new Tile(COLOR::BLUE, SHAPE::FOUR_STAR));
	tiles->add(new Tile(COLOR::BLUE, SHAPE::DIAMOND));
	tiles->add(new Tile(COLOR::BLUE, SHAPE::SQUARE));
	tiles->add(new Tile(COLOR::BLUE, SHAPE::SIX_STAR));
	tiles->add(new Tile(COLOR::BLUE, SHAPE::CLOVER));

	tiles->add(new Tile(COLOR::PURPLE, SHAPE::CIRCLE));
	tiles->add(new Tile(COLOR::PURPLE, SHAPE::FOUR_STAR));
	tiles->add(new Tile(COLOR::PURPLE, SHAPE::DIAMOND));
	tiles->add(new Tile(COLOR::PURPLE, SHAPE::SQUARE));
	tiles->add(new Tile(COLOR::PURPLE, SHAPE::SIX_STAR));
	tiles->add(new Tile(COLOR::PURPLE, SHAPE::CLOVER));
}

Game::Game() {
	tiles = nullptr;
	init_tiles();
}
Game::~Game() {

	for (int i = 0; i < tiles->size(); i++) {
		delete tiles->get(i);
	}

	delete tiles;
}

LinkedList* Game::getTiles() {
	return tiles;
}
#include "Menu.h"
#include "qwirkle_io.h"


Menu::Menu() {

}
Menu::~Menu() {

}


void Menu::run() {
	bool exit = false;


	while (!exit) {
		displayMenu();
		int option = getMenuChoice();

		switch (option) {

		case 1: {
			Game* game = newGame();
			displayMessage("\nLets play!\n\n");
			game->run();
			delete game;
			break;
		}
		case 2: {
			Game* game = loadGame();
			displayMessage("\nLets play!\n\n");
			game->run();
			delete game;
			break;
		}
		case 3: {
			displayMessage("\nShowing student info");
			break;
		}
		case 4: {
			displayMessage("\nGoodbye");
			exit = true;
			break;
		}
		default: {
			displayMessage("\nPlease select a valid option");
		}
		}
	}
}


Game* Menu::newGame() {
	displayMessage("\nStarting a new game");

	int playerCount;
	Player** players;
	Board* board;

	// Initialise Player count	
	playerCount = getPlayerCount();

	// Initialise Player array
	players = new Player * [playerCount - 1];

	// Initialise Player names
	for (int i = 0; i < playerCount; i++) {
		std::string id = std::to_string(i);
		std::string name = getPlayerName(i+1);
		players[i] = new Player(id, name);
	}
	
	// Initialise the board
	int boardSize;
	boardSize = getBoardSize();
	board = new Board(boardSize, boardSize);

	return new Game(board, players, playerCount);
}
Game* Menu::loadGame() {
	// Filename to store the name of the file received by the player
	std::string filename = getFilename();
	displayMessage("\nGame has successfully loaded");
}

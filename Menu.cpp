#include "Menu.h"
#include "qwirkle_io.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>


Menu::Menu() {

}
Menu::~Menu() {

}

// Run the game
void Menu::run() {

	bool exit = false;

	while (!exit) {

		displayMenu();
		int option = getMenuChoice();

		switch (option) {

			// Case for new game
			case 1: {
				Game* game = newGame();
				displayMessage("\nLets play!\n\n");
				game->run();
				delete game;
				break;
			}

			// Case for loading a game
			case 2: {
				Game* game = loadGame();
				if (game == nullptr) {
					displayMessage("\nInvalid File\n\n");
				}
				else {
					game->run();
				}
				// Game* game = loadGame();
				// displayMessage("\nLets play!\n\n");
				// game->run();
				// delete game;
				// break;
			}

			// Case for showing the student information
			case 3: {
				displayMessage("\nShowing student info");
				break;
			}

			// Case for exiting the game
			case 4: {
				displayMessage("\nGoodbye");
				exit = true;
				break;
			}

			// If the user enters an invalid option
			default: {
				displayMessage("\nPlease select a valid option");
			}
		}
	}
}

// Create new game and return it
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
	 Game* game = nullptr;

	 std::string filename = getFilename();
 	// Filename to store the name of the file received by the player
	 bool success = false;
	 std::string line;
	 int counter = 1;
	 int playercount = 0;
	 int boardsize = 0;
	 std::ifstream saveFile(filename);

	 int currentPlayer = 0;
	 std::vector<Player*> playersVector;
	 std::vector<std::pair<std::string, std::pair<int, int>>> boardTiles;
	 std::vector<std::vector<std::string>> playerHands;
	 std::vector<std::string> bagTiles;
	 std::cout << "Load File: " << filename << std::endl;
	 if (saveFile.is_open())
	 {
		 std::cout << "Open File" << std::endl;
		if (std::getline(saveFile, line)) {
			 playercount = std::stoi(line);
		 }
		std::cout << "player count: " << playercount << std::endl;

		 std::regex nametest("[A-Z]+");
		 std::regex scoretest("[0-9]+");
		 std::regex tiletest("([ROYGBP][1-6],){5}[ROYGBP][1-6]{1}");
		 std::regex tilebagtest("([ROYGBP][1-6],)*[ROYGBP][1-6]{1}$");
		 std::regex boardcolumntest("[0-9 ]+");
		 std::regex boardrowtest("([A-Z][ ][ ][|]{1})([ROYGBP ][1-6 ][|])+");
		 std::smatch m;


		 for (int i = 0; i < playercount; i++) {
			 std::cout << "get player(): " << i << std::endl;
			 // get first player
			 int counter = 1;
			 while (counter < 4) {
				 if (std::getline(saveFile, line)) {
					 std::cout << "player line: " << line << std::endl;
					 if (counter == 1 && std::regex_match(line, m, nametest)) {
						 playersVector.push_back(new Player(std::to_string(playercount + 1), line));
						 counter++;
					 }
					 else if (counter == 2 && std::regex_match(line.begin(), line.end(), scoretest)) {
						 playersVector.at(i)->addToScore(std::stoi(line));
						 counter++;
					 }
					 else if (counter == 3 && std::regex_match(line.begin(), line.end(), tiletest)) {
						 std::istringstream tiles(line);
						 std::string tile;
						 std::vector<std::string> hand;
						 while (std::getline(tiles, tile, ',')) {
							 hand.push_back(tile);
						 }
						 playerHands.push_back(hand);
						 counter++;
					 }
					 else {
						 std::cout << "player error" << counter << std::endl;
						 return nullptr;
					 }
				 }
				 std::cout << "counter: " << counter << std::endl;
			 }
		 }
		 if (std::getline(saveFile, line)) {
			 std::cout << "board line: " << line << std::endl;
			 if (std::regex_match(line.begin(), line.end(), boardcolumntest)) {

				 line.erase(line.begin(), line.end()-2);
				 boardsize = std::stoi(line) + 1;
				 std::cout << "boardsize: " << boardsize << std::endl;

				 std::getline(saveFile, line);
				 for (int row = 0; row < boardsize; row++) {
					 std::getline(saveFile, line);
					 std::cout << "rowline: " << line << std::endl;
					 if (!std::regex_match(line.begin(), line.end(), boardrowtest)) {
						 std::cout << "Invalid board row format" << std::endl;
						 break;
					 }
					 std::istringstream tiles(line);
					 std::string tile;
					 int column = -1;
					 while (std::getline(tiles, tile, '|')) {
						 if (column == -1) {
							 column++;
						 }
						 else {
							 if (tile == "  ") {
								 column++;
							 }
							 else {
								 std::pair<int, int> coord(row, column);
								 boardTiles.push_back(std::pair<std::string, std::pair<int, int>>(tile, coord));
								 std::cout << "tile" << tile << "[" << row << "," << column << "]" << std::endl;
								 column++;
							 }
						 }
					 }
				 }
			 }
			 else {
				 std::cout << "Invalid board format" << std::endl;
				 return nullptr;
			 }
		 }

		 if (std::getline(saveFile, line)) {
			 std::cout << "bag: " << line << std::endl;
			 if (std::regex_match(line.begin(), line.end(), tilebagtest)) {
				 std::istringstream tiles(line);
				 std::string tile;
				 while (std::getline(tiles, tile, ',')) {
					 bagTiles.push_back(tile);
				 }
			 }
			 else {
				 std::cout << "Invalid tile bag" << std::endl;
				 return nullptr;
			 }
		 }

		 if (std::getline(saveFile, line)) {
			 bool found = false;
			 for (int i = 0; i < playersVector.size(); i++) {
				 if (line == playersVector.at(i)->getName()) {
					 currentPlayer = i;
					 found = true;
					 success = true;
				 }

				 if (found == false) {
					 std::cout << "Current player can't be found" << std::endl;
					 return nullptr;
				 }
			 }
		 }

	 
		 saveFile.close();
		 Board* board = new Board(boardsize, boardsize);
		 Player** players = new Player * [playersVector.size()];
		 for (int i = 0; i < playersVector.size(); i++) {
			 Player* player = playersVector.at(i);
			 players[i] = player;
		 }
		 LinkedList* tilebagList = new LinkedList();
		 TileBag* tilebag = new TileBag(tilebagList);
		 game = new Game(board, players, playercount, tilebag, currentPlayer);

		 //initialise board
		 std::cout << "BoardTiles: " << std::endl;
		 for (int i = 0; i < boardTiles.size(); i++) {
			 std::pair<std::string, std::pair<int, int>> boardTile = boardTiles.at(i);
			 std::cout << "board tiles[" << i << "]: " << boardTile.first << std::endl;
			 int row = boardTile.second.first;
			 int col = boardTile.second.second;
			 std::cout << "tile" << boardTile.first << "[" << row << "," << col << "]" << std::endl;
			 board->setTile(game->getTile(boardTile.first), row, col);
			 
		 }

		 //initialise player hands
		 for (int i = 0; i < playerHands.size(); i++) {
			 std::vector<std::string> playerHand = playerHands.at(i);
			 Player* player = players[i];
			 for (int j = 0; j < playerHand.size(); j++) {
				 std::cout << "player Hand [" << j << "]: " << playerHand.at(j) << std::endl;
				 player->addToHand(game->getTile(playerHand.at(j)));
			 }
		 }

		 // intialise bag
		 for (int i = 0; i < bagTiles.size(); i++) {
			 std::cout << "bag Hand [" << i << "]: " << bagTiles.at(i) << std::endl;
			 tilebagList->add(game->getTile(bagTiles.at(i)));
		 }

	 }
	 else {
		 std::cout << "Unable to open save file" << std::endl;		 
	 }
	 return game;
 }

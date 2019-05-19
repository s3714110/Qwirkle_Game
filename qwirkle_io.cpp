#include "qwirkle_io.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>

/*

	Input Functions

*/
void displayMenu() {
	std::cout << "Welcome to qwirkle!" << std::endl;
	std::cout << "-------------------" << std::endl;
	std::cout << "Menu" << std::endl;
	std::cout << "----" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Show student information" << std::endl;
	std::cout << "4. Quit" << std::endl;
	std::cout << "\n" << std::endl;
}

void displayMessage(std::string message) {
	std::cout << message << std::endl;
}

void displayBoard(Board* board) {
	std::stringstream board_ss;
	int width = board->getWidth();
	int height = board->getHeight();

	board_ss << "   ";

	for (int j = 0; j < width; j++) {
		board_ss << std::setfill(' ') << std::setw(2) << j << " ";
	}
	board_ss << "\n";
	board_ss << "  ";
	for (int j = 0; j < width; j++) {
		board_ss << "---";
	}
	board_ss << "-\n";
	for (int i = 0; i < height; i++) {
		board_ss << char('A' + i) << " |";
		for (int j = 0; j < width; j++) {
			CellPtr cell = board->getCell(i, j);
			if (cell->getTile() == nullptr) {
				board_ss << "  ";
			}
			else {
				board_ss << cell->getTile()->toString();
			}
			board_ss << "|";
		}
		board_ss << "\n";
	}

	std::cout << board_ss.str() << std::endl;
	displayMessage("\n");
}

void displayScoreBoard(Player** players, int playerCount) {
	for (int i = 0; i < playerCount; i++) {
		std::cout << "Score for " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
	}
	displayMessage("\n");
}

void displayPlayerHand(Player* player) {
	LinkedList* hand = player->getPlayerHand();

	std::cout << "Your hand is: \n" << std::endl;
	for (int i = 0; i < hand->size(); i++) {
		Tile* tile = hand->get(i);
		if (i != 0) {
			std::cout << ", ";
		}
		std::cout << tile->toString() ;
	}
	std::cout << std::endl;
}

void displayHelp(){
	std::cout << "\n\nHelp\n" << std::endl;
	std::cout << "-----------------------------\n" << std::endl;
	std::cout << "To place a tile, enter:" << std::endl;
	std::cout << "place .. at .." << std::endl;
	std::cout << "For example, place G5 at B3\n" << std::endl;
	std::cout << "To replace a tile in your hand, enter:" << std::endl;
	std::cout << "replace .." << std::endl;
	std::cout << "For example, replace G5\n" << std::endl;
	std::cout << "To save the game, enter:" << std::endl;
	std::cout << "save <filename>" << std::endl;
	std::cout << "For example, save saveGame\n" << std::endl;
}

void displayEndgame(Player** players, int playerCount){

	Player* winner = players[0];

	std::cout << "\nGame over" << std::endl;
	for(int i=0; i < playerCount; i++){
		std::cout << "Score for " << players[i]->getName() << ": " << players[i]->getScore() << std::endl;
	}

	// Find the highest score and declare that player the winner!
	for(int i = 0; i < playerCount; i++){
		if(players[i]->getScore() > winner->getScore()){
			winner = players[i];
		}
	}
	std::cout << "Player " << winner->getName() << " won!\n" << std::endl;
	std::cout << "Goodbye!\n" << std::endl;
}

/*

	Input Functions

*/
int getMenuChoice() {

	int option = -1;

	do {
		option = getUserInput_menu();
		if (option < 0 || option > 4) {
			displayMessage("\nInvalid Option");
		}
	} while (option < 0 || option > 4);

	return option;
}

std::string getFilename() {
	displayMessage("\nEnter the filename from which to load the game");
	return getUserInput_filename();
}

int getPlayerCount() {
	int playerCount = -1;

	displayMessage("\nHow many players are there? (2-4)");
	do {
		playerCount = getUserInput_int();
		if (playerCount < 2) {
			displayMessage("\nInvalid Entry");
		}
	} while (playerCount < 2);

	return playerCount;
}

std::string getPlayerName(int playerNum) {
	std::string playerName = "";

	displayMessage("\nEnter a name for player " + std::to_string(playerNum) + " (uppercase characters only)");
	do {
		playerName = getUserInput_playername();
		if (playerName.size() == 0) {
			displayMessage("\nInvalid Player Name");
		}
	} while (playerName.size() == 0);

	return playerName;
}

int getBoardSize() {
	int boardSize = -1;

	displayMessage("\nEnter a board size (6-26)");
	do {
		boardSize = getUserInput_int();
		if (boardSize < 6 || boardSize > 26) {
			displayMessage("\nInvalid Board Size");
		}
	} while (boardSize < 6 || boardSize > 26);

	return boardSize;
}
std::vector<std::string> getPlayerMove() {
	std::cout << "\n>";

	return getUserInput_move();
}

int getUserInput_int() {
	int value = -1;

	std::string input;
	if (!getline(std::cin, input)) {
		return value;
	}

	std::regex _regex("^[0-9]+$");
	std::smatch m;

	if (std::regex_match(input, m, _regex) && input.size() < 8) {
		value = std::stoi(input);
	}

	return value;
}

std::string getUserInput_string() {
	std::string value = "";

	std::string input;
	if (!getline(std::cin, input)) {
		return value;
	}

	value = input;

	return value;
}

int getUserInput_menu() {
	int value = -1;

	std::string input;
	if (!getline(std::cin, input)) {
		return value;
	}

	std::regex _regex("^[1-4]$");
	std::smatch m;

	if (std::regex_match(input, m, _regex)) {
		value = std::stoi(input);
	}

	return value;
}

/*
	NEED TO IMPLEMENT

*/
std::string getUserInput_filename() {
	return getUserInput_string();
}

std::string getUserInput_playername() {
	std::string value = "";

	std::string input;

	if (!getline(std::cin, input)) {
		return value;
	}

	std::regex _regex("^[A-Z]*$");
	std::smatch m;

	if (std::regex_match(input, m, _regex)) {
		value = input;
	}


	return value;
}

std::string getUserInput_tile() {
	std::string value = "";

	std::string input;
	if (!getline(std::cin, input)) {
		return value;
	}

	std::regex _regex("^[ROYGBProygbp][123456]$");
	std::smatch m;

	if (std::regex_match(input, m, _regex)) {

		value = input;
	}

	return value;
}

std::vector<std::string> getUserInput_move() {
	std::vector<std::string> move;

	std::string input;
	if (!getline(std::cin, input)) {
		return move;
	}

	std::regex place_regex("^place [ROYGBP][1-6] at [A-Z][0-9][0-9]?$");
	std::regex replace_regex("^replace [ROYGBP][1-6]$");
	std::regex help_regex("help");
	std::smatch m;

	// get place
	if (std::regex_match(input, m, place_regex)) {
		std::size_t tile_pos = input.find_first_of(" ") + 1;
		std::size_t coord_pos = input.find_last_of(" ") + 1;

		move.push_back(input.substr(tile_pos, 2));
		move.push_back(input.substr(coord_pos));
	}

	// get replace
	else if (std::regex_match(input, m, replace_regex)) {
		std::size_t tile_pos = input.find_first_of(" ") + 1;
		move.push_back(input.substr(tile_pos));
	}

	// get help
	else if(std::regex_match(input, m, help_regex)){
		displayHelp();
	}

	// Display invalid move if they enter an invalid move
	else{
		displayMessage("\nInvalid Move\n");
	}

	return move;
}

#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>

#include "qwirkle_io.h"
#include "Menu.h"


Menu::Menu() {

}
Menu::~Menu() {

}

// Run the game
void Menu::run() {


		displayMenu();
		int option = getMenuChoice();

		while (true) {
			if (option == 1) {
				Game* game = newGame();
				displayMessage("\nLets play!\n\n");
				game->run();
				delete game;
				exit(EXIT_SUCCESS);
			}
			else if (option == 2) {
				Game* game = loadGame();
				if (game != nullptr) {
					game->run();
					delete game;
					exit(EXIT_SUCCESS);
				}
			}
			else if (option == 3) {
				displayMessage("\n-------------------------------------\n");
				displayMessage("Name: Nicholas Madew\n");
				displayMessage("Student ID: s3378373\n");
				displayMessage("Email: s3378373@student.rmit.edu.au\n\n");
				displayMessage("Name: Quinn Boukouvalas\n");
				displayMessage("Student ID: s3605398\n");
				displayMessage("Email: s3605398@student.rmit.edu.au\n\n");
				displayMessage("Name: Lam Hoang Tran\n");
				displayMessage("Student ID: s3714110\n");
				displayMessage("Email: s3714110@student.rmit.edu.au\n");
				displayMessage("\n------------------------------------\n");
				
				exit(EXIT_SUCCESS);
			}
			else if (option == 4) {
				displayMessage("\nGoodbye");
				exit(EXIT_SUCCESS);
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
	players = new Player * [playerCount];

	// Initialise Player names
	for (int i = 0; i < playerCount; i++) {
		std::string id = std::to_string(i);
		std::string name = getPlayerName(i+1);
		players[i] = new Player(id, name);
	}

	// Initialise the board
	board = new Board();

	return new Game(board, players, playerCount);
}

 Game* Menu::loadGame() {
	 Game* game = nullptr;

	 std::string filename = getFilename();
	 // Filename to store the name of the file received by the player

	 std::string line;

	 std::ifstream saveFile(filename);

	 int playercount = 0;
	 int boardwidth = 0;
	 int boardheight = 0;
	 int currentPlayer = -1;
	 std::vector<Player*> playersVector;
	 std::vector<std::pair<std::string, std::pair<int, int>>> boardTiles;
	 std::vector<std::vector<std::string>> playerHands;
	 std::vector<std::string> bagTiles;

	 std::cout << "Load File: " << filename << std::endl;


	 if (saveFile.is_open())
	 {
		 std::cout << "Open File" << std::endl;

		 std::regex nametest("[A-Z]+");
		 std::regex scoretest("[0-9]+");
		 std::regex tiletest("([ROYGBP][1-6],)*[ROYGBP][1-6]*");
		 std::regex tilebagtest("([ROYGBP][1-6],)*[ROYGBP][1-6]*$");
		 std::regex boardcolumntest("[0-9 ]+");
		 std::regex boardrowtest("([A-Z][ ][ ][|]{1})([ROYGBP ][1-6 ][|])+");
		 std::smatch m;

		 bool error = false;
		 while (std::getline(saveFile, line) && !error) {
			 if (saveFile.peek() == EOF) {
				 for (unsigned int i = 0; i < playersVector.size(); i++) {
					 if (0 == line.compare(playersVector.at(i)->getName())) {
						 currentPlayer = i;
					 }
				 }
			 }
			 else if (std::regex_match(line, m, nametest)) {
				 
				 playercount++;
				 playersVector.push_back(new Player(std::to_string(playercount), line));

				 int counter = 0;
				 if (std::getline(saveFile, line)) {
					 if (std::regex_match(line.begin(), line.end(), scoretest)) {
						 playersVector.at(playercount - 1)->addToScore(std::stoi(line));
						 counter++;
					 }
					 else {
						 error = true;
					 }
				 }
				 if (std::getline(saveFile, line) && ! error) {
					 if (std::regex_match(line.begin(), line.end(), tiletest)) {
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
						 error = true;
					 }
				 }
			 }
			 else if (std::regex_match(line.begin(), line.end(), boardcolumntest)) {

				 line.erase(line.begin(), line.end() - 2);
				 boardwidth = std::stoi(line) + 1;

				 std::getline(saveFile, line);
			 }
			 else if (std::regex_match(line.begin(), line.end(), boardrowtest)) {
				 int column = -1;
				 std::istringstream tiles(line);
				 std::string tile;
				 while (std::getline(tiles, tile, '|')) {
					 if (column == -1) {
						 column++;
					 }
					 else {
						 if (tile == "  ") {
							 column++;
						 }
						 else {
							 std::pair<int, int> coord(boardheight, column);
							 boardTiles.push_back(std::pair<std::string, std::pair<int, int>>(tile, coord));
							 column++;
						 }
					 }
				 }
				 boardheight++;
			 }
			 else if(std::regex_match(line.begin(), line.end(), tilebagtest)) {
				 std::istringstream tiles(line);
				 std::string tile;
				 while (std::getline(tiles, tile, ',')) {
					 bagTiles.push_back(tile);
				 }
			 }
			 else {
				 error = true;
			 }

		 }
		 saveFile.close();

		 if (!error) {
			 Board* board = new Board(boardheight, boardwidth);
			 Player** players = new Player * [playersVector.size()];
			 for (unsigned int i = 0; i < playersVector.size(); i++) {
				 Player* player = playersVector.at(i);
				 players[i] = player;
			 }
			 LinkedList* tilebagList = new LinkedList();
			 TileBag* tilebag = new TileBag(tilebagList);
			 game = new Game(board, players, playercount, tilebag, currentPlayer);

			 //initialise board
			 for (unsigned int i = 0; i < boardTiles.size(); i++) {
				std::pair<std::string, std::pair<int, int>> boardTile = boardTiles.at(i);
				int row = boardTile.second.first;
				int col = boardTile.second.second;

				board->setTile(game->getTile(boardTile.first), row, col);

			 }

			 //initialise player hands
			 for (unsigned int i = 0; i < playerHands.size(); i++) {
				 std::vector<std::string> playerHand = playerHands.at(i);
				 Player* player = players[i];
				 for (unsigned int j = 0; j < playerHand.size(); j++) {
					 player->addToHand(game->getTile(playerHand.at(j)));
				 }
			 }

			 // intialise bag
			 for (unsigned int i = 0; i < bagTiles.size(); i++) {
				 tilebagList->add(game->getTile(bagTiles.at(i)));
			 }
		 }
		 else {
			 displayMessage("Save File Corrupted");
		 }
	 }
	 else {
		displayMessage( "Save File Missing" );
	 }
	 return game;
 }

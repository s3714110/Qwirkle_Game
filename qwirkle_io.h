#pragma once
#include "Board.h"
#include "Player.h"
#include <vector>



void displayMenu();
void displayMessage(std::string message);
void displayBoard(Board* board);
void displayScoreBoard(Player** players, int playerCount);
void displayPlayerHand(Player* player);
void displayEndgame(Player** players, int playerCount);
void displayHelp();


int getMenuChoice();
std::string getFilename();
int getPlayerCount();
std::string getPlayerName(int playerNum);
int getBoardSize();
std::vector<std::string> getPlayerMove();

int getUserInput_int();
std::string getUserInput_string();
int getUserInput_menu();
std::string getUserInput_filename();
std::string getUserInput_playername();
std::string getUserInput_tile();
std::vector<std::string> getUserInput_move();

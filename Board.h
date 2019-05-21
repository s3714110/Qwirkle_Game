#pragma once
#include "Tile.h"
#include "LinkedList.h"
#include <map>
#include <vector>


#define _SPACE_ " "
#define _MAX_HEIGHT_ 26
#define _MAX_WIDTH_ 26

#define _INIT_HEIGHT_ 3
#define _INIT_WIDTH_ 3

// Row
#define _ROW_A_ "A"
#define _ROW_B_ "B"
#define _ROW_C_ "C"
#define _ROW_D_ "D"
#define _ROW_E_ "E"
#define _ROW_F_ "F"
#define _ROW_G_ "G"
#define _ROW_H_ "H"
#define _ROW_I_ "I"
#define _ROW_J_ "J"
#define _ROW_K_ "K"
#define _ROW_L_ "L"
#define _ROW_M_ "M"
#define _ROW_N_ "N"
#define _ROW_O_ "O"
#define _ROW_P_ "P"
#define _ROW_Q_ "Q"
#define _ROW_R_ "R"
#define _ROW_S_ "S"
#define _ROW_T_ "T"
#define _ROW_U_ "U"
#define _ROW_V_ "V"
#define _ROW_W_ "W"
#define _ROW_X_ "X"
#define _ROW_Y_ "Y"
#define _ROW_Z_ "Z"


const std::map<std::string, int> rows = {
  { _ROW_A_, 0 },
  { _ROW_B_, 1 },
  { _ROW_C_, 2 },
  { _ROW_D_, 3 },
  { _ROW_E_, 4 },
  { _ROW_F_, 5 },
  { _ROW_G_, 6 },
  { _ROW_H_, 7 },
  { _ROW_I_, 8 },
  { _ROW_J_, 9 },
  { _ROW_K_, 10 },
  { _ROW_L_, 11 },
  { _ROW_M_, 12 },
  { _ROW_N_, 13 },
  { _ROW_O_, 14 },
  { _ROW_P_, 15 },
  { _ROW_Q_, 16 },
  { _ROW_R_,17 },
  { _ROW_S_, 18 },
  { _ROW_T_, 19 },
  { _ROW_U_, 20 },
  { _ROW_V_, 21 },
  { _ROW_W_, 22 },
  { _ROW_X_, 23 },
  { _ROW_Y_, 24 },
  { _ROW_Z_, 25 }
};





// contains cell information
// tile is a pointer to a tile
class Cell {
private:
	int row;
	int col;
	Tile* tile;

public:
	Cell(int row, int col);

	int getRow();
	int getColumn();

	Tile* getTile();
	void setTile(Tile* tile);
	bool isEmpty();
	bool equal(Cell* cell);

	void update(int row, int col);
};

// This type is used to make the board
// each board element points to a cell


class Board {
private:
	static const int qwirkle = 6;
	static const int qwirkle_bonus = 6;

	static const int initHeight = 3;
	static const int initWidth = 3;
	static const int maxHeight = 26;
	static const int maxWidth = 26;


	std::vector <std::vector<Cell*>> board; // board[row][col]
	int height;
	int width;
	bool empty; // board is empty
	std::vector<Cell*> playerMoves;

	bool checkRow(int row, int col, Tile* tile);
	bool checkColumn(int row, int col, Tile* tile);
	bool checkPlayerMoves(int row, int col);

	LinkedList* getRow(int row, int col);
	LinkedList* getColumn(int row, int col);

	int rowPoints(Cell* playerMove);
	int columnPoints(Cell* playerMove);
	
public:
	Board();
	Board(int height, int width);
	~Board();

	int getHeight();
	int getWidth();
	Cell* getCell(int row, int col);

	void setTile(Tile* tile, int row, int col);
	bool placeTile(Tile* tile, int row, int col);
	bool validMove(Tile* tile, int row, int col);
	int getPoints();


	bool colorMatch(LinkedList* tiles, Tile* tile);
	bool shapeMatch(LinkedList* tiles, Tile* tile);

	void insertRow(int row);
	void insertColumn(int col);
	void updateCells();

};
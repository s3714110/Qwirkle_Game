#pragma once
#include "Tile.h"
#include "LinkedList.h"
#include <map>


#define _SPACE_ " "

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

// Column
#define _COL_0_ "0"
#define _COL_1_ "1"
#define _COL_2_ "2"
#define _COL_3_ "3"
#define _COL_4_ "4"
#define _COL_5_ "5"
#define _COL_6_ "6"
#define _COL_7_ "7"
#define _COL_8_ "8"
#define _COL_9_ "9"
#define _COL_10_ "10"
#define _COL_11_ "11"
#define _COL_12_ "12"
#define _COL_13_ "13"
#define _COL_14_ "14"
#define _COL_15_ "15"
#define _COL_16_ "16"
#define _COL_17_ "17"
#define _COL_18_ "18"
#define _COL_19_ "19"
#define _COL_20_ "20"
#define _COL_21_ "21"
#define _COL_22_ "22"
#define _COL_23_ "23"
#define _COL_24_ "24"
#define _COL_25_ "25"


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
const std::map<int, std::string> columns = {
  { 0, _COL_0_ },
  { 1, _COL_1_ },
  { 2, _COL_2_ },
  { 3, _COL_3_ },
  { 4, _COL_4_ },
  { 5, _COL_5_ },
  { 6, _COL_6_ },
  { 7, _COL_7_ },
  { 8, _COL_8_ },
  { 9, _COL_9_ },
  { 10, _COL_10_ },
  { 11, _COL_11_ },
  { 12, _COL_12_ },
  { 13, _COL_13_ },
  { 14, _COL_14_ },
  { 15, _COL_15_ },
  { 16, _COL_16_ },
  { 17, _COL_17_ },
  { 18, _COL_18_ },
  { 19, _COL_19_ },
  { 20, _COL_20_ },
  { 21, _COL_21_ },
  { 22, _COL_22_ },
  { 23, _COL_23_ },
  { 24, _COL_24_ },
  { 25, _COL_25_ }
};



typedef enum _ROW {
	ROW_A,
	ROW_B,
	ROW_C,
	ROW_D,
	ROW_E,
	ROW_F,
	ROW_G,
	ROW_H,
	ROW_I,
	ROW_J,
	ROW_K,
	ROW_L,
	ROW_M,
	ROW_N,
	ROW_O,
	ROW_P,
	ROW_Q,
	ROW_R,
	ROW_S,
	ROW_T,
	ROW_U,
	ROW_V,
	ROW_W,
	ROW_X,
	ROW_Y,
	ROW_Z,
} ROW;

typedef enum _COLUMN {
	COL_0,
	COL_1,
	COL_2,
	COL_3,
	COL_4,
	COL_5,
	COL_6,
	COL_7,
	COL_8,
	COL_9,
	COL_10,
	COL_11,
	COL_12,
	COL_13,
	COL_14,
	COL_15,
	COL_16,
	COL_17,
	COL_18,
	COL_19,
	COL_20,
	COL_21,
	COL_22,
	COL_23,
	COL_24,
	COL_25
} COLUMN;


// contains cell information
// tile is a pointer to a tile
class Cell {
private:
	ROW row;
	COLUMN col;
	Tile* tile;

public:
	Cell(ROW row, COLUMN col);

	ROW getRow();
	COLUMN getColumn();

	Tile* getTile();
	void setTile(Tile* tile);
	bool isEmpty();
};

// This type is used to make the board
// each board element points to a cell
typedef Cell* CellPtr;

class Board {
private:
	CellPtr** board; // board[row][col]
	int height;
	int width;
	bool empty; // board is empty

	bool checkRow(int row, int col, Tile* tile);
	bool checkColumn(int row, int col, Tile* tile);

	bool colorMatch(LinkedList* tiles, Tile* tile);
	bool shapeMatch(LinkedList* tiles, Tile* tile);

	LinkedList* getRow(int row, int col);
	LinkedList* getColumn(int row, int col);

	int getPoints(Tile* tile, int row, int col);

public:
	Board(int row, int col);
	~Board();

	int getHeight();
	int getWidth();
	CellPtr getCell(int row, int col);

	bool placeTile(Tile* tile, int row, int col, int& points);
	bool isValidMove(Tile* tile, int row, int col);
};
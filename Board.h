#ifndef _BOARD_
#define _BOARD_
#include <map>
#include <vector>


//#include "Tile.h"
#include "LinkedList.h"


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

	bool checkRowMatch(LinkedList* tileRow, Tile* tile);
	bool checkColumnMatch(LinkedList* tileRow, Tile* tile);
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
#endif
#include "Board.h"
#include <iostream>

// Cells are empty when created
Cell::Cell(ROW row, COLUMN col) {
	Cell::row = row;
	Cell::col = col;
	tile = nullptr;
}

ROW Cell::getRow() {
	return row;
}
COLUMN Cell::getColumn() {
	return col;
}
Tile* Cell::getTile() {
	return tile;
}
void Cell::setTile(Tile* tile) {
	Cell::tile = tile;
}
bool Cell::isEmpty() {
	if (tile == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

// Create the board with empty cells
Board::Board(int height, int width) {
	this->height = height;
	this->width = width;
	empty = true;

	board = new CellPtr*[height];
	for (int i = 0; i < height; i++) {
		board[i] = new CellPtr[width];
		for (int j = 0; j < width; j++) {
			board[i][j] = new Cell(static_cast<ROW>(i), static_cast<COLUMN>(j));
		}
	}
}

// Destroy all Cell objects
// Tile objects are not destroyed
Board::~Board() {

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete board[i][j];
		}
		delete board[i];
	}
}

int Board::getHeight() {
	return height;
}
int Board::getWidth() {
	return width;
}
CellPtr Board::getCell(int row, int col) {
	return board[row][col];
}

void Board::setTile(Tile* tile, int row, int col) {
	board[row][col]->setTile(tile);
}
// Places tile on the board at position (row, col)
bool Board::placeTile(Tile* tile, int row, int col, int& points) {

	bool placeTile = false;
	placeTile = isValidMove(tile, row, col);


	if (placeTile) {
		board[row][col]->setTile(tile);
		points = getPoints(tile, row, col);

		// if board was empty need to update 'empty' variable
		if (empty) {
			empty = false;
		}
	}

	return placeTile;
}

// Only checks that the row and col are within the dimensions
// and cell is not empty
// Need to add game rules
bool Board::isValidMove(Tile* tile, int row, int col) {
	bool isValid = false;

	if (row >= height || row < 0) {
		isValid = false;
	}
	else if (col >= width || col < 0) {
		isValid = false;
	}
	else if (!board[row][col]->isEmpty()) {
		isValid = false;
	}
	else if (!checkRow(row, col, tile) && !checkColumn(row, col, tile)) {
		isValid = false;
	}
	else {
		isValid = true;
	}

	
	return isValid;
}

bool Board::checkRow(int row, int col, Tile* tile) {
	bool valid = false;

	LinkedList* tileRow = getRow(row,col);
	

	if (tileRow->size() > 5) {
		valid = false;
	}
	else if (tileRow->contains(tile)) {
		valid = false;
	}
	else if (!shapeMatch(tileRow, tile) && !colorMatch(tileRow, tile)) {
		valid = false;
	}
	else if (tileRow->size() == 0 && !empty) {
		valid = false;
	}
	else {
		valid = true;
	}

	delete tileRow;

	return valid;
}
bool Board::checkColumn(int row, int col, Tile* tile) {
	bool valid = false;

	LinkedList* tileColumn = getColumn(row,col);


	if (tileColumn->size() > 5) {
		valid = false;
	}
	else if (tileColumn->contains(tile)) {
		valid = false;
	}
	else if (!shapeMatch(tileColumn, tile) && !colorMatch(tileColumn, tile)) {
		valid = false;
	}
	else if (tileColumn->size() == 0 && !empty) {
		valid = false;
	}
	else {
		valid = true;
	}

	delete tileColumn;

	return valid;
}

bool Board::colorMatch(LinkedList* tiles, Tile* tile) {
	bool valid = true;

	for (int i = 0; i < tiles->size(); i++) {
		if (tile->getColor() != tiles->get(i)->getColor()) {
			valid = false;
		}
	}

	return valid;
}

bool Board::shapeMatch(LinkedList* tiles, Tile* tile) {
	bool valid = true;

	for (int i = 0; i < tiles->size(); i++) {
		if (tile->getShape() != tiles->get(i)->getShape()) {
			valid = false;
		}
	}

	return valid;
}

LinkedList* Board::getRow(int row, int col) {
	LinkedList* tileRow = new LinkedList();

	// Add Left	
	int addCol = col - 1;
	if (addCol >= 0) {
		Cell* cell = board[row][addCol];
		while (cell->getTile() != nullptr) {

			tileRow->add(cell->getTile());

			// End of Row
			if (addCol == 0) {
				break;
			}

			addCol--;
			cell = board[row][addCol];
		}
	}

	// Add Right
	addCol = col + 1;
	if (addCol < width) {
		Cell* cell = board[row][addCol];
		while (cell->getTile() != nullptr) {

			tileRow->add(cell->getTile());

			// End of Row
			if (addCol == width - 1) {
				break;
			}

			addCol++;
			cell = board[row][addCol];
		}
	}


	return tileRow;
}

LinkedList* Board::getColumn(int row, int col) {
	LinkedList* tileColumn = new LinkedList();

	// Add Left	
	int addRow = row - 1;
	if (addRow >= 0) {
		Cell* cell = board[addRow][col];
		while (cell->getTile() != nullptr) {

			tileColumn->add(cell->getTile());

			// End of Row
			if (addRow == 0) {
				break;
			}

			addRow--;
			cell = board[addRow][col];
		}
	}

	// Add Down
	addRow = row + 1;
	if (addRow < height) {
		Cell* cell = board[addRow][col];
		while (cell->getTile() != nullptr) {

			tileColumn->add(cell->getTile());

			// End of Row
			if (addRow == height - 1) {
				break;
			}

			addRow++;
			cell = board[addRow + 1][col];
		}
	}

	return tileColumn;
}

int Board::getPoints(Tile* tile, int row, int col) {

	int points = 0;

	LinkedList* tileRow = getRow(row, col);
	LinkedList* tileColumn = getColumn(row, col);

	if (tileRow->size() > 0) {
		tileRow->add(tile);

		points += tileRow->size();

		// if qwirkle
		if (tileRow->size() == 6) {
			points += 6;
		}
	}

	if (tileColumn->size() > 0) {
		tileColumn->add(tile);
		points += tileColumn->size();

		// if qwirkle
		if (tileColumn->size() == 6) {
			points += 6;
		}
	}


	delete tileRow;
	delete tileColumn;

	return points;
}
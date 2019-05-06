#include "Board.h"
#include <sstream>

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
	Board::height = height;
	Board::width = width;

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

// Used to output board to console
std::string Board::toString() {
	std::stringstream board_ss;

	board_ss << "   ";

	for (int j = 0; j < width; j++) {
		board_ss << columns.find(j)->second << "  ";
	}
	board_ss << "\n";
	board_ss << "  ";
	for (int j = 0; j < width; j++) {
		board_ss << "---";
	}
	board_ss << "-\n";
	for (int i = 0; i < height; i++) {
		board_ss << columns.find(i)->second << " |";
		for (int j = 0; j < width; j++) {
			CellPtr cell = board[i][j];
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

	return board_ss.str();
}

// Places tile on the board at position (row, col)
bool Board::placeTile(Tile* tile, int row, int col) {

	bool placeTile = false;
	placeTile = isValidMove(tile, row, col);


	if (placeTile) {
		board[row][col]->setTile(tile);
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
	else {
		isValid = true;
	}

	
	return isValid;
}


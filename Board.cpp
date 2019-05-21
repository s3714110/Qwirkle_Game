#include "Board.h"
#include <iostream>
#include <vector>

// Cells are empty when created
Cell::Cell(int row, int col) {
	this->row = row;
	this->col = col;
	tile = nullptr;
}

int Cell::getRow() {
	return row;
}
int Cell::getColumn() {
	return col;
}
Tile* Cell::getTile() {
	return tile;
}

void Cell::update(int row, int col) {
	this->row = row;
	this->col = col;
}
void Cell::setTile(Tile* tile) {
	this->tile = tile;
}
bool Cell::isEmpty() {
	if (tile == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
bool Cell::equal(Cell* cell) {
	bool equal = false;
	if (col == cell->getColumn() && row == cell->getRow()) {
		equal = true;
	}
	return equal;
}

// Create the board with empty cells
Board::Board() {
	height = _INIT_HEIGHT_;
	width = _INIT_WIDTH_;
	empty = true;
	for (int i = 0; i < height; i++) {
		std::vector<Cell*> cellRow(width);
		for (int j = 0; j < width; j++) {
			cellRow[j] = new Cell(i, j);
		}
		board.push_back(cellRow);
	}
}
Board::Board(int height, int width) {
	this->height = height;
	this->width = width;
	empty = true;

	for (int i = 0; i < height; i++) {
		std::vector<Cell*> cellRow(width);
		for (int j = 0; j < width; j++) {
			cellRow[j] = new Cell(i, j);
		}
		board.push_back(cellRow);
	}
}

// Destroy all Cell objects
// Tile objects are not destroyed
Board::~Board() {

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			delete board[i][j];
		}
	}
}


int Board::getHeight() {
	return height;
}
int Board::getWidth() {
	return width;
}
Cell* Board::getCell(int row, int col) {
	return board[row][col];
}

void Board::setTile(Tile* tile, int row, int col) {
	board[row][col]->setTile(tile);
}
// Places tile on the board at position (row, col)
bool Board::placeTile(Tile* tile, int row, int col) {

	bool placeTile = false;

	if (validMove(tile, row, col)) {
		board[row][col]->setTile(tile);

		playerMoves.push_back(board[row][col]);
		// if board was empty need to update 'empty' variable
		if (empty) {
			empty = false;
		}
		
		// check if board needs to be expanded
		if (row == 0) {
			insertRow(row);
		}
		else if (row == width - 1) {
			insertRow(width);
		}
		if (col == 0) {
			insertColumn(col);
		}
		else if (col == height - 1) {
			insertColumn(height);
		}
	}

	return placeTile;
}

// Only checks that the row and col are within the dimensions
// and cell is not empty
// Need to add game rules
bool Board::validMove(Tile* tile, int row, int col) {
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
	else if (!checkPlayerMoves(row,col)) {
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
bool Board::checkPlayerMoves(int row, int col) {
	bool valid = true;

	if (!playerMoves.empty()) {
		for (int i = 0; i < playerMoves.size(); i++) {
			if (row != playerMoves.at(i)->getRow() && col != playerMoves.at(i)->getColumn()) {
				valid = false;
			}
		}
	}

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
			cell = board[addRow][col];
		}
	}

	return tileColumn;
}

int Board::getPoints() {

	int points = 0;

	std::vector<int> countedRows;
	std::vector<int> countedColumns;

	for (int i = 0; i < playerMoves.size(); i++) {
		bool countRow = true;
		bool countColumn = true;

		Cell* playerMove = playerMoves.at(i);
		for (int j = 0; j < countedRows.size(); j++) {
			if (playerMove->getRow() == countedRows.at(j)) {
				countRow = false;
			}
		}
		for (int j = 0; j < countedColumns.size(); j++) {
			if (playerMove->getColumn() == countedColumns.at(j)) {
				countColumn = false;
			}
		}

		
		if (countRow) {
			int rowPoint = rowPoints(playerMove);
			points += rowPoint;
			countedRows.push_back(playerMove->getRow());
					//points += rowPoints(playerMove);
		}
		if (countColumn) {
			int colPoint = columnPoints(playerMove);
			points += colPoint;
			countedColumns.push_back(playerMove->getColumn());
			//points += columnPoints(playerMove);
		}
	}

	playerMoves.clear();
	return points;
}

int Board::rowPoints(Cell* playerMove) {
	int count = 0;
	
	int row = playerMove->getRow();
	int col = playerMove->getColumn();

	LinkedList* tileRow = getRow(row, col);
	count = tileRow->size();

	// if the row isnt empty count this tile as well
	if (count > 0) {
		count++;
	}
	if (count == qwirkle) {
		count += qwirkle_bonus;
	}

	delete tileRow;

	return count;
}
int Board::columnPoints(Cell* playerMove) {
	int count = 0;

	int row = playerMove->getRow();
	int col = playerMove->getColumn();
	LinkedList* tileColumn = getColumn(row, col);
	count = tileColumn->size();

	// if the column isnt empty count this tile as well
	if (count > 0) {
		count++;
	}
	if (count == qwirkle) {
		count += qwirkle_bonus;
	}

	delete tileColumn;

	return count;
}


void Board::insertRow(int row) {

	std::vector<Cell*> cellRow(width);
	for (int i = 0; i < width; i++) {
		cellRow[i] = new Cell(row, i);
	}

	if (row == 0) {
		board.insert(board.begin(), cellRow);
		updateCells();
		height++;
	}
	else if (row == height) {
		board.push_back(cellRow);
		height++;
	}
	
}

void Board::insertColumn(int col) {

	if (col == 0) {
		for (int i = 0; i < height; i++) {
			board[i].insert(board[i].begin(), new Cell(i, col));
		}
		updateCells();
		width++;
	}
	else if (col == width) {
		for (int i = 0; i < height; i++) {
			board[i].push_back(new Cell(i, col));
		}
		width++;
	}	
}

void Board::updateCells() {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			board[i][j]->update(i, j);
		}
	}
}


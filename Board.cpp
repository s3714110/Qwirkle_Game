#include <iostream>
#include <vector>

#include "Board.h"


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
// used when a new game is created
Board::Board() {
	height = initHeight;
	width = initWidth;
	empty = true;
	for (int i = 0; i < height; i++) {
		std::vector<Cell*> cellRow(width);
		for (int j = 0; j < width; j++) {
			cellRow[j] = new Cell(i, j);
		}
		board.push_back(cellRow);
	}
}

// Create the board with empty cells
// used to create a board when a game is loaded
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
// if game rules are satisfied
// returns truue if tiles was placed
bool Board::placeTile(Tile* tile, int row, int col) {

	bool placeTile = false;

	if (validMove(tile, row, col)) {
		board[row][col]->setTile(tile);
		placeTile = true;

		playerMoves.push_back(board[row][col]);
		// if board was empty need to update 'empty' variable
		if (empty) {
			empty = false;
		}
		
		// check if board needs to be expanded
		if (row == 0) {
			insertRow(row);
		}
		else if (row == height - 1) {
			insertRow(height);
		}
		if (col == 0) {
			insertColumn(col);
		}
		else if (col == width - 1) {			
			insertColumn(width);
		}
	}

	return placeTile;
}

/*
	Implements the checks to satisty the game rules.

	Input:
		Tile* tile	- the tile that is to be placed
		int row		- indicates row where the tile is placed
		int col		- indicates column where the tile is placed
		

	Return:
		bool valid	- matches either shape or color with the other
					  tiles in the row

	Note:
		This method is used to check the rules of the game.
*/
bool Board::validMove(Tile* tile, int row, int col) {
	bool valid = false;

	LinkedList* tileRow = getRow(row, col);
	LinkedList* tileColumn = getColumn(row, col);

	// if the row is outside the board dimensions (invalid)
	if (row >= height || row < 0) {
		valid = false;
	}
	// if the column is outside the board dimensions (invalid)
	else if (col >= width || col < 0) {
		valid = false;
	}
	// if the cell is not empty (invalid)
	else if (!board[row][col]->isEmpty()) {
		std::cout << "Cell Not Empty" << std::endl;
		valid = false;
	}
	// if the row and column are empty and the board is not empty (invalid)
	else if (tileRow->size() == 0 && tileColumn->size() == 0 && !empty) {
		std::cout << "Row and Column Empty" << std::endl;
		valid = false;
	}
	// if the row or column are already full (invalid)
	else if (tileRow->size() == qwirkle || tileColumn->size() == qwirkle) {
		std::cout << "Row or Column Qwirkle" << std::endl;
		valid = false;
	}
	// if the row or column already contain the tile (invalid)
	else if (tileRow->contains(tile) || tileColumn->contains(tile)) {
		std::cout << "Row or column contain tile" << std::endl;
		valid = false;
	}
	// if the row check does not match and row is not empty (invalid)
	else if (!checkRowMatch(tileRow, tile) && tileRow->size() > 0){
		std::cout << "Row does not match" << std::endl;
		valid = false;
	}
	// if the row check does not match and row is not empty (invalid)
	else if (!checkColumnMatch(tileColumn,tile) && tileColumn->size() > 0) {
		std::cout << "Column does not match" << std::endl;
		valid = false;
	}
	// if not on same line with other tiles in the current move (invalid)
	else if (!checkPlayerMoves(row,col)) {
		std::cout << "Player previous moves dont match" << std::endl;
		valid = false;
	}
	// move is valid
	else {
		std::cout << "Valid move" << std::endl;
		valid = true;
	}

	delete tileRow;
	delete tileColumn;


	return valid;
}

/*
	Checks row where the player placed the tile to see if it is a valid move.
	Checks the color or shape match conditions.

	Input:
		LinkedList* tileRow	- list of tiles in the row where the tile will be placed
		Tile* tile	- the tile that is to be placed

	Return:
		if shape or color match
				return true	
		else	
				return false

	Note:
		This method is used to check the rules of the game.
*/
bool Board::checkRowMatch(LinkedList* tileRow, Tile* tile) {
	return shapeMatch(tileRow, tile) || colorMatch(tileRow, tile);
}

/*
	Checks column where the player placed the tile to see if it is a valid move.
	Checks the color or shape match conditions.

	Input:
		LinkedList* tileColumn	- list of tiles in the column where the tile will be placed
		Tile* tile				- the tile that is to be placed

	Return:
		if shape or color match
				return true
		else
				return false

	Note:
		This method is used to check the rules of the game.
*/
bool Board::checkColumnMatch(LinkedList* tileColumn, Tile* tile) {
	return shapeMatch(tileColumn, tile) || colorMatch(tileColumn, tile);
}

/*
	Checks the players next move to see if it is on the same row or column
	as their previous moves.

	Input:
		int row - indicates row where the tile is placed
		int col - indicates column where the tile is placed

	Return:
		bool valid	- new tile location matches the row or column of the previous
					  placed tiles then the move is valid

	Note:
		This method is used to check the rules of the game.
*/
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

/*
	Checks the color match condition.
	Checks the list of tiles against the player tile.

	Input:
		LinkedList* tiles	- list of conneted tiles already on the board
		Tile* tile			- tile to be placed by player

	Return:
		bool valid	- if the color of the player tile matches the color
					  of the tiles in the list then the move is valid

	Note:
		This method is used to check the rules of the game.
*/
bool Board::colorMatch(LinkedList* tiles, Tile* tile) {
	bool valid = true;

	for (int i = 0; i < tiles->size(); i++) {
		if (tile->getColor() != tiles->get(i)->getColor()) {
			valid = false;
		}
	}

	return valid;
}

/*
	Checks the shape match condition.
	Checks the list of tiles against the player tile.

	Input:
		LinkedList* tiles	- list of conneted tiles already on the board
		Tile* tile			- tile to be placed by player

	Return:
		bool valid	- if the shape of the player tile matches the shape
					  of the tiles in the list then the move is valid

	Note:
		This method is used to check the rules of the game.
*/
bool Board::shapeMatch(LinkedList* tiles, Tile* tile) {
	bool valid = true;

	for (int i = 0; i < tiles->size(); i++) {
		if (tile->getShape() != tiles->get(i)->getShape()) {
			valid = false;
		}
	}

	return valid;
}

/*
	Gets a list of tiles connected in a row to the cell at coord (row,col)

	Input:
		int row - indicates row where the tile is placed
		int col - indicates column where the tile is placed

	Return:
		LinkedList* tileRow - List of tiles connected to the this tile

	Note:
		the list is used to check the rules of the game
*/
LinkedList* Board::getRow(int row, int col) {
	LinkedList* tileRow = new LinkedList();

	// Add Left	
	int addCol = col - 1;
	
	if (addCol >= 0) {
		Cell* cell = board[row][addCol];
		while (cell->getTile() != nullptr && addCol >= 0) {

			cell = board[row][addCol];
			tileRow->add(cell->getTile());
			
			addCol--;			
		}
	}

	// Add Right
	addCol = col + 1;
	if (addCol < width) {
		Cell* cell = board[row][addCol];
		while (cell->getTile() != nullptr && addCol < width) {

			cell = board[row][addCol];
			tileRow->add(cell->getTile());
			
			addCol++;
		}
	}


	return tileRow;
}

/*
	Gets a list of tiles connected in a column to the cell at coord (row,col)

	Input:
		int row - indicates row where the tile is placed
		int col - indicates column where the tile is placed

	Return:
		LinkedList* tileColumn - List of tiles connected to the this tile

	Note:
		the list is used to check the rules of the game
*/
LinkedList* Board::getColumn(int row, int col) {
	LinkedList* tileColumn = new LinkedList();

	// Add Left	
	int addRow = row - 1;
	if (addRow >= 0) {
		Cell* cell = board[addRow][col];
		while (cell->getTile() != nullptr && addRow >= 0) {
			
			cell = board[addRow][col];
			tileColumn->add(cell->getTile());

			addRow--;
		}
	}

	// Add Down
	addRow = row + 1;
	if (addRow < height) {
		Cell* cell = board[addRow][col];
		while (cell->getTile() != nullptr && addRow < height) {

			cell = board[addRow][col];
			tileColumn->add(cell->getTile());


			addRow++;			
		}
	}

	return tileColumn;
}

/*
	Calculate the total points score for the players move. The function 
	will calculate the score for each tile that was placed. Making sure not
	to count the row or column twice.

	Input:
		Cell* playerMove - indicates cell where the tile was placed

	Return:
		int points - total number of points scored for each move

*/
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

/*
	Calculate the points scored on the row

	Input:
		Cell* playerMove - indicates cell where the tile was placed

	Return:
		int points - number of points scored on this row

	Note:
		if the row is empty then the player will not score any
		points on the row
*/
int Board::rowPoints(Cell* playerMove) {
	int points = 0;
	
	int row = playerMove->getRow();
	int col = playerMove->getColumn();

	// gets a list of tiles on the row that are connected to the tile
	LinkedList* tileRow = getRow(row, col);
	points = tileRow->size();

	// if the row isnt empty count this tile as well
	if (points > 0) {
		points++;
	}
	// if the player scored a qwirkle on the row
	if (points == qwirkle) {
		points += qwirkle_bonus;
	}

	delete tileRow;

	return points;
}

/*
	Calculate the points scored on the column

	Input:
		Cell* playerMove - indicates cell where the tile was placed

	Return:
		int points - number of points scored on this row

	Note:
		if the column is empty then the player will not score any 
		points on the column
*/
int Board::columnPoints(Cell* playerMove) {
	int points = 0;

	int row = playerMove->getRow();
	int col = playerMove->getColumn();

	// gets a list of tiles on the column that are connected to the tile
	LinkedList* tileColumn = getColumn(row, col);
	points = tileColumn->size();

	// if the column isnt empty count this tile as well
	if (points > 0) {
		points++;
	}
	// if the player scored a qwirkle on the column
	if (points == qwirkle) {
		points += qwirkle_bonus;
	}

	delete tileColumn;

	return points;
}

/*
	Insert a new row into the board

	Input:
		int row - indicates where the new row will be added

	Note:
		if row == 0			(new column added at the top of the board)
		if row == height	(new column added at the bottom of the board)
*/
void Board::insertRow(int row) {

	std::vector<Cell*> cellRow(width);
	for (int i = 0; i < width; i++) {
		cellRow[i] = new Cell(row, i);
	}

	if (row == 0) {
		board.insert(board.begin(), cellRow);
		height++;
		updateCells();		
	}
	else if (row == height) {
		board.push_back(cellRow);
		height++;
	}
	
}

/*
	Insert a new column into the board

	Input:
		int col - indicates where the new column will be added

	Note:
		if col == 0		(new column added on the left of the board)
		if col == width	(new column added on the right of the board)
*/
void Board::insertColumn(int col) {

	if (col == 0) {
		for (int i = 0; i < height; i++) {
			board[i].insert(board[i].begin(), new Cell(i, col));
		}
		width++;
		updateCells();
	}
	else if (col == width) {
		for (int i = 0; i < height; i++) {
			board[i].push_back(new Cell(i, col));
		}
		width++;
	}	
}

/*
	Updates the Cells row and column
	This method is called after the board is expanded
*/
void Board::updateCells() {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			board[i][j]->update(i, j);
		}
	}
}


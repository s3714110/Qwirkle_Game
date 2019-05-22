#include "Tile.h"
#include <sstream>

Tile::Tile(COLOR color, SHAPE shape) {
	this->color = color;
	this->shape = shape;
}

COLOR Tile::getColor() {
	return color;
}

SHAPE Tile::getShape() {
	return shape;
}

bool Tile::equal(Tile* tile) {
	bool equal = false;

	if (tile != nullptr) {

		if (color == tile->getColor() && shape == tile->getShape()) {
			equal = true;
		}
	}

	return equal;

}
bool Tile::sameColor(Tile* tile) {
	if (tile == nullptr) {
		return false;
	}
	return color == tile->getColor();
}
bool Tile::sameShape(Tile* tile) {
	if (tile == nullptr) {
		return false;
	}
	return shape == tile->getShape();
}
std::string Tile::toString() {
	std::stringstream tile_ss;

	switch (color) {
		case RED: {
			tile_ss << _RED_;
			break;
		}
		case ORANGE: {
			tile_ss << _ORANGE_;
			break;
		}
		case YELLOW: {
			tile_ss << _YELLOW_;
			break;
		}
		case GREEN: {
			tile_ss << _GREEN_;
			break;
		}
		case BLUE: {
			tile_ss << _BLUE_;
			break;
		}
		case PURPLE: {
			tile_ss << _PURPLE_;
			break;
		}
	}

	switch (shape) {
		case CIRCLE: {
			tile_ss << _CIRCLE_;
			break;
		}
		case FOUR_STAR: {
			tile_ss << _FOUR_STAR_;
			break;
		}
		case DIAMOND: {
			tile_ss << _DIAMOND_;
			break;
		}
		case SQUARE: {
			tile_ss << _SQUARE_;
			break;
		}
		case SIX_STAR: {
			tile_ss << _SIX_STAR_;
			break;
		}
		case CLOVER: {
			tile_ss << _CLOVER_;
			break;
		}
	}

	return tile_ss.str();
}

std::string Tile::toStringUnicode() {
	std::stringstream tile_ss;
	if (color == RED){
		tile_ss << REDCOLOR;
	}

	else if(color == ORANGE){
		tile_ss << ORANGECOLOR;
	}
	
	else if(color == YELLOW){
		tile_ss << YELLOWCOLOR;
	}

	else if(color == GREEN){
		tile_ss << GREENCOLOR;
	}

	else if(color == BLUE){
		tile_ss << BLUECOLOR;
	}
	
	else if(color == PURPLE){
		tile_ss << PURPLECOLOR;
	}

	if (shape == CIRCLE){
		tile_ss << CIRCLESHAPE << RESETCOLOR;
	}

	else if(shape == FOUR_STAR){
		tile_ss << FOURSTARSHAPE << RESETCOLOR;
	}

	else if(shape == DIAMOND){
		tile_ss << DIAMONDSHAPE << RESETCOLOR;
	}

	else if(shape == SQUARE){
		tile_ss << SQUARESHAPE << RESETCOLOR;
	}

	else if(shape == SIX_STAR){
		tile_ss << SIXSTARSHAPE << RESETCOLOR;
	}

	else if(shape == CLOVER){
		tile_ss << CLOVERSHAPE << RESETCOLOR;
	}

	return tile_ss.str();
}
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
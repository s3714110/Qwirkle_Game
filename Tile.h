#ifndef _TILE_
#define _TILE_

#include <string>


// Color
#define _RED_ 'R'
#define _ORANGE_ 'O'
#define _YELLOW_ 'Y'
#define _GREEN_ 'G'
#define _BLUE_ 'B'
#define _PURPLE_ 'P'

// Shape
#define _CIRCLE_ 1
#define _FOUR_STAR_ 2
#define _DIAMOND_ 3
#define _SQUARE_ 4
#define _SIX_STAR_ 5
#define _CLOVER_ 6


typedef enum _COLOR {
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE
} COLOR;

typedef enum _SHAPE {
	CIRCLE,
	FOUR_STAR,
	DIAMOND,
	SQUARE,
	SIX_STAR,
	CLOVER
} SHAPE;

class Tile {
private:
	COLOR color;
	SHAPE shape;

public:
	Tile(COLOR color, SHAPE shape);
	COLOR getColor();
	SHAPE getShape();
	bool equal(Tile* tile);
	bool sameColor(Tile* tile);
	bool sameShape(Tile* tile);
	std::string toString();
};
#endif
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

// Color escape codes
#define RESETCOLOR   "\033[0m"
#define REDCOLOR     "\033[31m"      
#define ORANGECOLOR     "\033[1m\033[31m"      
#define YELLOWCOLOR  "\033[33m"      
#define GREENCOLOR   "\033[32m"     
#define BLUECOLOR    "\033[34m"      
#define PURPLECOLOR "\033[35m"

// Shape unicode
#define CIRCLESHAPE "\xE2\x9A\xAB"
#define FOURSTARSHAPE "\342\234\246 "
#define DIAMONDSHAPE "\xF0\x9F\x94\xB6"
#define SQUARESHAPE "\xE2\x97\xBC "
#define SIXSTARSHAPE "\u2736 "
#define CLOVERSHAPE "\xF0\x9F\x8D\x80"


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
	std::string toStringUnicode();
};
#endif
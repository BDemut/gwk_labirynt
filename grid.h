#ifndef GRID
#define GRID


#include <GL/glew.h>
#include "object.h"
#include <random>

class GridTile {
private:
	int layout;
	float r, g, b;
public:
	void draw();
	GridTile(int, int, int, int);
	GridTile();
	int getLayout();
	std::vector<Object> objects;
};

class Grid {
private:
public:
	GridTile*** gridTiles;
	int x, y, z;
	void draw();
	Grid();
	GridTile*** getTiles();
};

const int CONTAINS_ALL =		0b0000111111;	//only walls, ceiling and floor, no ramps
const int CONTAINS_FLOOR =		0b0000000001;
const int CONTAINS_WALL_BACK =	0b0000000010;
const int CONTAINS_WALL_RIGHT =	0b0000000100;
const int CONTAINS_WALL_FRONT =	0b0000001000;
const int CONTAINS_WALL_LEFT =	0b0000010000;
const int CONTAINS_CEILING =	0b0000100000;
const int CONTAINS_RAMP_LR =	0b0001000000;
const int CONTAINS_RAMP_FB =	0b0010000000;
const int CONTAINS_RAMP_RL =	0b0100000000;
const int CONTAINS_RAMP_BF =	0b1000000000;

const int X_SIZE = 15;
const int Y_SIZE = 4;
const int Z_SIZE = 15;

const float defaultGTBounds[6] = { -1.0f, 1.0f, 0.0f, 2.0f, -1.0f, 1.0f };
#endif

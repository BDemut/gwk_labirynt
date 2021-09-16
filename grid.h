#ifndef GRID
#define GRID


#include <GL/glew.h>
#include "object.h"
#include <random>

class GridTile {
private:
	std::vector<Object> objects;
	float r, g, b;
public:
	void draw();
	GridTile(int, int, int, int);
	GridTile();
};

class Grid {
private:
	GridTile*** gridTiles;
	int x_size;
	int y_size;
	int z_size;
public:
	void draw();
	Grid();
};

const int CONTAINS_ALL =		0b111111;
const int CONTAINS_FLOOR =		0b000001;
const int CONTAINS_WALL_BACK =	0b000010;
const int CONTAINS_WALL_RIGHT =	0b000100;
const int CONTAINS_WALL_FRONT =	0b001000;
const int CONTAINS_WALL_LEFT =	0b010000;
const int CONTAINS_CEILING =	0b100000;

#endif

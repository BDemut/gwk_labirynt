#ifndef GRID
#define GRID


#include <GL/glew.h>
#include "object.h"

class GridTile {
private:
	Object* objects;
	int objectCount;
public:
	void draw();
	GridTile();
};

#endif

#include "grid.h"

GridTile::GridTile() {
	objects = new Object[6];
	objects[0] = Object(FLOOR_SCALE, FLOOR_TRANSLATION);
	objects[1] = Object(CEILING_SCALE,CEILING_TRANSLATION);
	objects[2] = Object(WALL_BACK_SCALE,WALL_BACK_TRANSLATION);
	objects[3] = Object(WALL_LEFT_SCALE,WALL_LEFT_TRANSLATION);
	objects[4] = Object(WALL_FRONT_SCALE,WALL_FRONT_TRANSLATION);
	objects[5] = Object(WALL_RIGHT_SCALE,WALL_RIGHT_TRANSLATION);
	objectCount = 6;
}

void GridTile::draw() {
	for (int i = 0; i < objectCount; i++)
		objects[i].draw();
}
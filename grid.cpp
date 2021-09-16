#include "grid.h"

GridTile::GridTile() {
	objects = std::vector<Object>();
	objects.push_back(Object());
	objects.push_back(Object());
	objects.push_back(Object());
	objects.push_back(Object());
	objects.push_back(Object());
	objects.push_back(Object());
}

GridTile::GridTile(int layout, int x, int y, int z) {
	r = (float)rand() / RAND_MAX;
	g = (float)rand() / RAND_MAX;
	b = (float)rand() / RAND_MAX;
	objects = std::vector<Object>();
	for (int i = 0; i < OBJECT_MAX; i++)
		if (layout & 1) {
			objects.push_back(Object(i, x, y, z));
			layout >>= 1;
		}
}



void GridTile::draw() {
	for (int i = 0; i < objects.size(); i++)
		objects[i].draw(r,g,b);
}

Grid::Grid() {
	x_size = 10;
	y_size = 3;
	z_size = 10;

	gridTiles = new GridTile * *[x_size];
	for (int x = 0; x < x_size; x++) {
		gridTiles[x] = new GridTile * [y_size];
		for (int y = 0; y < y_size; y++) {
			gridTiles[x][y] = new GridTile[z_size];
			for (int z = 0; z < z_size; z++) {
				gridTiles[x][y][z] = GridTile(CONTAINS_ALL, x,y,z);
			}
		}
	}
}

void Grid::draw() {
	for (int x = 0; x < x_size; x++) {
		for (int y = 0; y < y_size; y++) {
			for (int z = 0; z < z_size; z++) {
				gridTiles[x][y][z].draw();
			}
		}
	}
}
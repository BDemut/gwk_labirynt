#include "grid.h"

int generatePath(int*** layout, int start_x, int start_z, int recursionDepth) {
	int totalLength = 0;
	int curr_x = start_x;
	int curr_z = start_z;
	int failedMovesInARow = 0;
	while (true) {
		int direction = rand() % 4;
		switch (direction) {
		case 0:
			if (curr_z > 0 && layout[curr_x][0][curr_z - 1] == CONTAINS_ALL) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_BACK;
				layout[curr_x][0][curr_z - 1] = layout[curr_x][0][curr_z - 1] & ~CONTAINS_WALL_FRONT;
				curr_z--;
				totalLength++;
				failedMovesInARow = 0;
			}
			else failedMovesInARow++;
			break;
		case 1:
			if (curr_x > 0 && layout[curr_x - 1][0][curr_z] == CONTAINS_ALL) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_LEFT;
				layout[curr_x - 1][0][curr_z] = layout[curr_x - 1][0][curr_z] & ~CONTAINS_WALL_RIGHT;
				curr_x--;
				totalLength++;
				failedMovesInARow = 0;
			}
			else failedMovesInARow++;
			break;
		case 2:
			if (curr_z < Z_SIZE - 1 && layout[curr_x][0][curr_z + 1] == CONTAINS_ALL) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_FRONT;
				layout[curr_x][0][curr_z + 1] = layout[curr_x][0][curr_z + 1] & ~CONTAINS_WALL_BACK;
				curr_z++;
				totalLength++;
				failedMovesInARow = 0;
			}
			else failedMovesInARow++;
			break;
		case 3:
			if (curr_x < X_SIZE - 1 && layout[curr_x + 1][0][curr_z] == CONTAINS_ALL) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_RIGHT;
				layout[curr_x + 1][0][curr_z] = layout[curr_x + 1][0][curr_z] & ~CONTAINS_WALL_LEFT;
				curr_x++;
				totalLength++;
				failedMovesInARow = 0;
			}
			else failedMovesInARow++;
			break;
		}

		int rollBranch = rand() % 100;
		int rollEnd = rand() % 100;
		if (rollBranch > 70 && recursionDepth < 3) {
			totalLength += generatePath(layout, curr_x, curr_z, recursionDepth + 1);
		}
		if (failedMovesInARow > 5) {
			return totalLength;
		}
	}

	/*
	if (length < 2) {
		if (curr_z > 0) {
			if (rollBack > 30) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_BACK;
				layout[curr_x][0][curr_z - 1] = layout[curr_x][0][curr_z - 1] & ~CONTAINS_WALL_FRONT;
				generatePath(layout, curr_x, curr_z - 1, length + 1);
			}
		}

		if (curr_x > 0) {
			if (rollLeft > 30) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_LEFT;
				layout[curr_x - 1][0][curr_z] = layout[curr_x - 1][0][curr_z] & ~CONTAINS_WALL_RIGHT;
				generatePath(layout, curr_x - 1, curr_z, length + 1);
			}
		}

		if (curr_z < Z_SIZE - 1) {
			if (rollFront > 30) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_FRONT;
				layout[curr_x][0][curr_z + 1] = layout[curr_x][0][curr_z + 1] & ~CONTAINS_WALL_BACK;
				generatePath(layout, curr_x, curr_z + 1, length +1);
			}
		}

		if (curr_x < X_SIZE - 1) {
			if (rollBack > 30) {
				layout[curr_x][0][curr_z] = layout[curr_x][0][curr_z] & ~CONTAINS_WALL_RIGHT;
				layout[curr_x + 1][0][curr_z] = layout[curr_x + 1][0][curr_z] & ~CONTAINS_WALL_LEFT;
				generatePath(layout, curr_x + 1, curr_z, length + 1);
			}
		}
	}
	*/
	
}

int generateLayout(int*** out) {
	return generatePath(out, 0, 0, 0);
}

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
	for (int i = 0; i < OBJECT_MAX; i++) {
		if (layout & 1) {
			objects.push_back(Object(i, x, y, z));
		}
		layout >>= 1;
	}
}



void GridTile::draw() {
	for (int i = 0; i < objects.size(); i++)
		objects[i].draw(r,g,b);
}

Grid::Grid() {
	int l = 0;
	int attempts = 0;
	int*** layout = new int** [X_SIZE];
	do {
		for (int x = 0; x < X_SIZE; x++) {
			layout[x] = new int* [Y_SIZE];
			for (int y = 0; y < Y_SIZE; y++) {
				layout[x][y] = new int[Z_SIZE];
				for (int z = 0; z < Z_SIZE; z++) {
					layout[x][y][z] = CONTAINS_ALL;
				}
			}
		}
		l = generateLayout(layout);
		attempts++;
	} while (l < 70);

	gridTiles = new GridTile * *[X_SIZE];
	for (int x = 0; x < X_SIZE; x++) {
		gridTiles[x] = new GridTile * [Y_SIZE];
		for (int y = 0; y < Y_SIZE; y++) {
			gridTiles[x][y] = new GridTile[Z_SIZE];
			for (int z = 0; z < Z_SIZE; z++) {
				gridTiles[x][y][z] = GridTile(layout[x][y][z], x,y,z);
			}
		}
	}
}

void Grid::draw() {
	for (int x = 0; x < X_SIZE; x++) {
		for (int y = 0; y < Y_SIZE; y++) {
			for (int z = 0; z < Z_SIZE; z++) {
				gridTiles[x][y][z].draw();
			}
		}
	}
}
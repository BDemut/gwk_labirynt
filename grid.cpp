#include "grid.h"

bool step(int*** layout, int& curr_x, int curr_y, int& curr_z, int direction) {
	switch (direction) {
	case 0:
		if (curr_z > 0 && layout[curr_x][curr_y][curr_z - 1] == CONTAINS_ALL) {
			layout[curr_x][curr_y][curr_z] = layout[curr_x][curr_y][curr_z] & ~CONTAINS_WALL_BACK;
			layout[curr_x][curr_y][curr_z - 1] = layout[curr_x][curr_y][curr_z - 1] & ~CONTAINS_WALL_FRONT;
			curr_z--;
			return true;
		}
		break;
	case 1:
		if (curr_x > 0 && layout[curr_x - 1][curr_y][curr_z] == CONTAINS_ALL) {
			layout[curr_x][curr_y][curr_z] = layout[curr_x][curr_y][curr_z] & ~CONTAINS_WALL_LEFT;
			layout[curr_x - 1][curr_y][curr_z] = layout[curr_x - 1][curr_y][curr_z] & ~CONTAINS_WALL_RIGHT;
			curr_x--;
			return true;
		}
		break;
	case 2:
		if (curr_z < Z_SIZE - 1 && layout[curr_x][curr_y][curr_z + 1] == CONTAINS_ALL) {
			layout[curr_x][curr_y][curr_z] = layout[curr_x][curr_y][curr_z] & ~CONTAINS_WALL_FRONT;
			layout[curr_x][curr_y][curr_z + 1] = layout[curr_x][curr_y][curr_z + 1] & ~CONTAINS_WALL_BACK;
			curr_z++;
			return true;
		}
		break;
	case 3:
		if (curr_x < X_SIZE - 1 && layout[curr_x + 1][curr_y][curr_z] == CONTAINS_ALL) {
			layout[curr_x][curr_y][curr_z] = layout[curr_x][curr_y][curr_z] & ~CONTAINS_WALL_RIGHT;
			layout[curr_x + 1][curr_y][curr_z] = layout[curr_x + 1][curr_y][curr_z] & ~CONTAINS_WALL_LEFT;
			curr_x++;
			return true;
		}
		break;
	}
	return false;
}

int generatePath(int*** layout, int start_x, int start_y, int start_z, int recursionDepth) {
	int totalLength = 0;
	int curr_x = start_x;
	int curr_y = start_y;
	int curr_z = start_z;
	int failedMovesInARow = 0;
	while (true) {
		int direction = rand() % 4;
		if (step(layout, curr_x, curr_y, curr_z, direction)) {
			totalLength++;
			failedMovesInARow = 0;

			int rollVertical = rand() % 100;
			if (rollVertical > 90 && curr_y < Y_SIZE - 1) {
				int ramp_x = curr_x;
				int ramp_y = curr_y;
				int ramp_z = curr_z;
				if (step(layout, curr_x, curr_y + 1, curr_z, direction)) {
					curr_y++;
					switch (direction) {
					case 0:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_BF;
						break;
					case 1:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_LR;
						break;
					case 2:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_FB;
						break;
					case 3:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_RL;
						break;
					}
					layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] & ~CONTAINS_CEILING;
					layout[ramp_x][ramp_y + 1][ramp_z] = layout[ramp_x][ramp_y + 1][ramp_z] & ~CONTAINS_FLOOR;
				}
			}
			if (rollVertical < 10 && curr_y > 0) {
				int ramp_x = curr_x;
				int ramp_y = curr_y - 1;
				int ramp_z = curr_z;
				if (step(layout, curr_x, curr_y - 1, curr_z, direction)) {
					curr_y--;
					switch (direction) {
					case 0:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_FB;
						break;
					case 1:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_RL;
						break;
					case 2:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_BF;
						break;
					case 3:
						layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] | CONTAINS_RAMP_LR;
						break;
					}
					layout[ramp_x][ramp_y][ramp_z] = layout[ramp_x][ramp_y][ramp_z] & ~CONTAINS_CEILING;
					layout[ramp_x][ramp_y + 1][ramp_z] = layout[ramp_x][ramp_y + 1][ramp_z] & ~CONTAINS_FLOOR;
				}
			}
		}
		else failedMovesInARow++;

		int rollBranch = rand() % 100;

		if (rollBranch > 70 && recursionDepth < 3) {
			totalLength += generatePath(layout, curr_x, curr_y, curr_z, recursionDepth + 1);
		}
		if (failedMovesInARow > 5) {
			return totalLength;
		}
	}
}

int generateLayout(int*** out) {
	return generatePath(out, 0, 0, 0, 0);
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

GridTile::GridTile(int l, int x, int y, int z) {
	r = (float)rand() / RAND_MAX;
	g = (float)rand() / RAND_MAX;
	b = (float)rand() / RAND_MAX;
	objects = std::vector<Object>();
	layout = l;
	for (int i = 0; i < OBJECT_MAX; i++) {
		if (l & 1) {
			objects.push_back(Object(i, x, y, z));
		}
		l >>= 1;
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
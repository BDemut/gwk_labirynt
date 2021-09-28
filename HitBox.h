#pragma once

#include <glm/glm.hpp>

class HitBox
{
public:
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	int hmXsize = 32;
	int hmZsize = 32;

	bool usable;

	int hitboxType;

	float** heightMap;

	glm::ivec3 tile;

	unsigned int indices[24] =
	{
		0,1,
		0,2,
		0,4,
		1,3,
		1,5,
		2,3,
		2,6,
		3,7,
		4,5,
		4,6,
		5,7,
		6,7
	};

	float* hitboxVerts = new float[32];

	HitBox(float* vertices, int count, int type);
	HitBox(float* vertices, int count, int y, int type);
	HitBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, int type);
	HitBox(int type, int y, int internalType, glm::ivec3 tile);
	HitBox();
	void trans(glm::mat4 M, glm::vec2* tab);
	void trans2(glm::mat4 M, float* tab);
	void interpolateMap(float** map, int xSize, int zSize, float x0, float x1, float z0, float z1);

private:
	void calculateHitBox(float* vertices, int count);
	void calculateVerts();
};

const int WALLS = 0;
const int FLOOR = 1;
const int CEIL = 2;
const int RAMPS = 3;
const int OTHER = 4;
const int CAMERA = 5;

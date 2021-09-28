#include "HitBox.h"

HitBox::HitBox(float* vertices, int count, int type) 
{
	calculateHitBox(vertices, count);
	calculateVerts();
	usable = true;
	this->hitboxType = type;
	heightMap = NULL;
}

HitBox::HitBox(float* vertices, int count, int y, int type)
{
	calculateHitBox(vertices, count);
	calculateVerts();
	usable = true;
	this->hitboxType = type;
	heightMap = new float* [hmXsize];
	for (int i = 0; i < hmXsize; i++)
	{
		heightMap[i] = new float[hmZsize];
	}
	if (type == 1)
	{
		for (int i = 0; i < hmXsize; i++)
		{
			for (int j = 0; j < hmZsize; j++)
			{
				this->heightMap[i][j] = y * 2 + 0.1;
			}
		}
	}
	else if (type == 2)
		for (int i = 0; i < hmXsize; i++)
		{
			for (int j = 0; j < hmZsize; j++)
			{
				this->heightMap[i][j] = y * 2 + 1.9;
			}
		}
}


HitBox::HitBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, int type)
{
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
	this->minZ = minZ;
	this->maxZ = maxZ;
	calculateVerts();
	usable = true;
	this->hitboxType = type;
}
HitBox::HitBox(int y, int type, int internalType, glm::ivec3 tile)
{
	this->minX = -0.7f;
	this->maxX = 0.7f;
	this->minY = -1.0f;
	this->maxY = 1.0f;
	this->minZ = -0.7f;
	this->maxZ = 0.7f;
	calculateVerts();
	usable = true;
	this->hitboxType = type;
	this->tile = glm::ivec3(tile);
	hmXsize = 2;
	hmZsize = 2;
	heightMap = new float* [hmXsize];
	for (int i = 0; i < hmXsize; i++)
	{
		heightMap[i] = new float[hmZsize];
	}
	if (internalType == 6)
	{
		//interpolateMap(heightMap, hmXsize, hmZsize, y * 2, (y+1) * 2, y*2, y*2);
		heightMap[0][0] = y * 2;
		heightMap[0][1] = y * 2;
		heightMap[1][0] = y * 2 + 2.2;
		heightMap[1][1] = y * 2 + 2.2;
	}
	else if (internalType == 7)
	{
		//interpolateMap(heightMap, hmXsize, hmZsize, (y+1) * 2, y * 2, y*2, y*2);
		heightMap[0][0] = y * 2 + 2.2;
		heightMap[0][1] = y * 2;
		heightMap[1][0] = y * 2 + 2.2;
		heightMap[1][1] = y * 2;
	}
	else if (internalType == 8)
	{
		//interpolateMap(heightMap, hmXsize, hmZsize, y * 2, y * 2, (y+1) * 2, y * 2);
		heightMap[0][0] = y * 2 + 2.2;
		heightMap[0][1] = y * 2 + 2.2;
		heightMap[1][0] = y * 2;
		heightMap[1][1] = y * 2;
	}
	else if (internalType == 9)
	{
		//interpolateMap(heightMap, hmXsize, hmZsize, y * 2, y * 2, y * 2, (y + 1) * 2);
		heightMap[0][0] = y * 2;
		heightMap[0][1] = y * 2 + 2.2;
		heightMap[1][0] = y * 2;
		heightMap[1][1] = y * 2 + 2.2;
	}
}
HitBox::HitBox()
{
	minX = maxX = minY = maxY = minZ = maxZ = 0;
	usable = false;
	this->hitboxType = 4;
}

void HitBox::interpolateMap(float** map, int xSize, int zSize, float x0, float x1, float z0, float z1)
{
	for (int i = 0; i < xSize; i++)
	{
		float tempX = x0 * (xSize -1 - i) / (float)(xSize-1) + x1 * ( i / (float)(xSize - 1));
		for (int j = 0; j < xSize; j++)
		{
			float tempZ= z0 * (zSize - 1 - j) / (float)(zSize - 1) + z1 * (j / (float)(zSize - 1));
			map[i][j] = tempX + tempZ;
		}
	}
}

void HitBox::calculateHitBox(float* vertices, int count)
{
	maxX = minX = NULL;
	maxY = minY = NULL;
	maxZ = minZ = NULL;
	for (int i = 0; i < count * 4; i += 4)
	{
		if (vertices[i] < minX)
			minX = vertices[i];
		if (vertices[i] > maxX)
			maxX = vertices[i];
		if (vertices[i + 1] < minY)
			minY = vertices[i + 1];
		if (vertices[i + 1] > maxY)
			maxY = vertices[i + 1];
		if (vertices[i + 2] < minZ)
			minZ = vertices[i + 2];
		if (vertices[i + 2] > maxZ)
			maxZ = vertices[i + 2];
	}
}

void HitBox::calculateVerts()
{
	hitboxVerts[0] = minX;
	hitboxVerts[1] = maxY;
	hitboxVerts[2] = maxZ;
	hitboxVerts[3] = 1.0f;

	hitboxVerts[4] = maxX;
	hitboxVerts[5] = maxY;
	hitboxVerts[6] = maxZ;
	hitboxVerts[7] = 1.0f;

	hitboxVerts[8] = minX;
	hitboxVerts[9] = minY;
	hitboxVerts[10] = maxZ;
	hitboxVerts[11] = 1.0f;

	hitboxVerts[12] = maxX;
	hitboxVerts[13] = minY;
	hitboxVerts[14] = maxZ;
	hitboxVerts[15] = 1.0f;

	hitboxVerts[16] = minX;
	hitboxVerts[17] = maxY;
	hitboxVerts[18] = minZ;
	hitboxVerts[19] = 1.0f;

	hitboxVerts[20] = maxX;
	hitboxVerts[21] = maxY;
	hitboxVerts[22] = minZ;
	hitboxVerts[23] = 1.0f;

	hitboxVerts[24] = minX;
	hitboxVerts[25] = minY;
	hitboxVerts[26] = minZ;
	hitboxVerts[27] = 1.0f;

	hitboxVerts[28] = maxX;
	hitboxVerts[29] = minY;
	hitboxVerts[30] = minZ;
	hitboxVerts[31] = 1.0f;
}
void HitBox::trans(glm::mat4 M, glm::vec2* tab)
{
	glm::vec4 temp = glm::vec4(minX, maxY, minZ, 1.0f);
	temp = M * temp;
	tab[0] = glm::vec2(temp.x, temp.z);

	temp = glm::vec4(minX, maxY, maxZ, 1.0f);
	temp = M * temp;
	tab[1] = glm::vec2(temp.x, temp.z);

	temp = glm::vec4(maxX, maxY, maxZ, 1.0f);
	temp = M * temp;
	tab[2] = glm::vec2(temp.x, temp.z);

	temp = glm::vec4(maxX, maxY, minZ, 1.0f);
	temp = M * temp;
	tab[3] = glm::vec2(temp.x, temp.z);
}

void HitBox::trans2(glm::mat4 M, float* tab)
{
	glm::vec4 temp = glm::vec4(minX, minY, minZ, 1.0f);
	temp = M * temp;
	tab[0] = temp.y;

	temp = glm::vec4(minX, maxY, minZ, 1.0f);
	temp = M * temp;
	tab[1] = temp.y;
}
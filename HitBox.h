#pragma once

#include <glm/glm.hpp>

class HitBox
{
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

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

	HitBox(float* vertices, int count);

	void calculateHitBox(float* vertices, int count);
	void calculateVerts();
	void trans(glm::mat4 M, glm::vec2* tab);
};


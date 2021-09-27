#include "HitBox.h"

HitBox::HitBox(float* vertices, int count) 
{
	calculateHitBox(vertices, count);
	calculateVerts();
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
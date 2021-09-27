#include "Collisions.h"

void Collisions::getAxes(glm::vec2* tabVerts, glm::vec2* axes)
{
	glm::vec2 edge;
	//axes = new glm::vec2[4];
	for (int i = 0; i < 4; i++)
	{
		edge = tabVerts[i % 4] - tabVerts[(i + 1) % 4];
		axes[i] = glm::vec2(-edge.y, edge.x);
	}
}
void Collisions::proj(glm::vec2 axis, glm::vec2* verts, float* projection)
{
	float min = glm::dot(axis, verts[0]);
	float max = min;
	float temp;
	for (int i = 1; i < 4; i++)
	{
		temp = glm::dot(axis, verts[i]);
		if (temp < min)
			min = temp;
		else if (temp > max)
			max = temp;
	}
	projection[0] = min;
	projection[1] = max;
}
bool Collisions::detectCollision(HitBox* obj1, glm::mat4 M1, HitBox* obj2, glm::mat4 M2)
{
	glm::vec2 tabVerts1[4];
	glm::vec2 tabVerts2[4];
	obj1->trans(M1, tabVerts1);
	obj2->trans(M2, tabVerts2);

	glm::vec2 axesObj1[4];
	glm::vec2 axesObj2[4];

	getAxes(tabVerts1, axesObj1);
	getAxes(tabVerts2, axesObj2);

	float* proj1 = new float[2];
	float* proj2 = new float[2];

	for (int i = 0; i < 4; i++)
	{
		proj(axesObj1[i], tabVerts1, proj1);
		proj(axesObj1[i], tabVerts2, proj2);
		if (!(proj1[0] < proj2[1] && proj1[1] > proj2[0]))
			return false;
	}

	for (int i = 0; i < 4; i++)
	{
		proj(axesObj2[i], tabVerts1, proj1);
		proj(axesObj2[i], tabVerts2, proj2);
		if (!(proj1[0] < proj2[1] && proj1[1] > proj2[0]))
			return false;
	}

	float zCoords1[2];
	float zCoords2[2];
	obj1->trans2(M1, zCoords1);
	obj2->trans2(M2, zCoords2);

	if (!(zCoords1[0] < zCoords2[1] && zCoords1[1] > zCoords2[0]))
		return false;

	return true;
}

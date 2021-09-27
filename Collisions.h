#pragma once

#include <glm/glm.hpp>
#include "HitBox.h"

class Collisions
{
public:
	static void getAxes(glm::vec2* tabVerts, glm::vec2* axes);
	static void proj(glm::vec2 axis, glm::vec2* verts, float* projection);
	static bool detectCollision(HitBox* obj1, glm::mat4 M1, HitBox* obj2, glm::mat4 M2);

private:
	Collisions() {};
};


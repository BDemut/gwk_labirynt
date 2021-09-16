#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "allmodels.h"

class Object {
private:
	glm::vec3 scale;
	glm::vec3 translation;
public:
	void draw(float,float,float);
	Object(int, int, int, int);
	Object();
};

const int OBJECT_FLOOR = 0;
const int OBJECT_WALL_BACK = 1;
const int OBJECT_WALL_RIGHT = 2;
const int OBJECT_WALL_FRONT = 3;
const int OBJECT_WALL_LEFT = 4;
const int OBJECT_CEILING = 5;

const int OBJECT_MAX = 6;

const float SCALES[OBJECT_MAX][3] = {
	{1.0, 0.05, 1.0},
	{1.0, 1.0, 0.05},
	{0.05, 1.0, 1},
	{1.0, 1.0, 0.05},
	{0.05, 1.0, 1},
	{1.0, 0.05, 1.0}
};

const float TRANSLATIONS[OBJECT_MAX][3] = {
	{0, 0.05, 0},
	{0, 1, -0.95},
	{0.95, 1, 0},
	{0, 1, 0.95},
	{-0.95, 1, 0},
	{0, 1.95, 0}
};

#endif OBJECT_H


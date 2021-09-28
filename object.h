#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "allmodels.h"
#include "HitBox.h"

class Object {
private:
	glm::vec3 scale;
	glm::vec3 translation;
	glm::vec3 rotation;
	float rotationAngle;
	int type;
public:
	void draw(float,float,float);
	Object(int, int, int, int);
	Object();

	glm::mat4 getM();
	glm::mat4 getRotationMatrix();
	glm::mat4 getTSMatrix();
	HitBox hitbox;
};

const int OBJECT_FLOOR = 0;
const int OBJECT_WALL_BACK = 1;
const int OBJECT_WALL_RIGHT = 2;
const int OBJECT_WALL_FRONT = 3;
const int OBJECT_WALL_LEFT = 4;
const int OBJECT_CEILING = 5;
const int OBJECT_RAMP_LR = 6;
const int OBJECT_RAMP_FB = 8;
const int OBJECT_RAMP_RL = 7;
const int OBJECT_RAMP_BF = 9;

const int OBJECT_MAX = 10;

const float SCALES[OBJECT_MAX][3] = {
	{1.0, 0.05, 1.0},
	{1.0, 1.0, 0.05},
	{0.05, 1.0, 1},
	{1.0, 1.0, 0.05},
	{0.05, 1.0, 1},
	{1.0, 0.05, 1.0},
	{1.35, 0.05, 1.0},
	{1.0, 0.05, 1.35},
	{1.35, 0.05, 1.0},
	{1.0, 0.05, 1.35},
};

const float TRANSLATIONS[OBJECT_MAX][3] = {
	{0, 0.05, 0},
	{0, 1, -0.95},
	{0.95, 1, 0},
	{0, 1, 0.95},
	{-0.95, 1, 0},
	{0, 1.95, 0},
	{0, 1, 0},
	{0, 1, 0},
	{0, 1, 0},
	{0, 1, 0}
};

const float ROTATIONS[OBJECT_MAX][4] = {
	{-10,0,0,0},
	{-10,0,0,0},
	{-10,0,0,0},
	{-10,0,0,0},
	{-10,0,0,0},
	{-10,0,0,0},
	{-PI / 4,0,0,1},
	{-PI / 4,1,0,0},
	{PI / 4,0,0,1},
	{PI / 4,1,0,0},
};



#endif OBJECT_H


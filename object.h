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
	void draw();
	Object(glm::vec3, glm::vec3);
	Object();
};

const glm::vec3 FLOOR_SCALE =				glm::vec3(1.0, 0.05, 1.0);
const glm::vec3 FLOOR_TRANSLATION =			glm::vec3(0, 0.05, 0);
const glm::vec3 WALL_BACK_SCALE =			glm::vec3(1.0, 1.0, 0.05);
const glm::vec3 WALL_BACK_TRANSLATION =		glm::vec3(0, 1, -0.95);
const glm::vec3 WALL_LEFT_SCALE =			glm::vec3(0.05, 1.0, 1);
const glm::vec3 WALL_LEFT_TRANSLATION =		glm::vec3(-0.95, 1, 0);
const glm::vec3 WALL_RIGHT_SCALE =			glm::vec3(0.05, 1.0, 1);
const glm::vec3 WALL_RIGHT_TRANSLATION =	glm::vec3(0.95, 1, 0);
const glm::vec3 WALL_FRONT_SCALE =			glm::vec3(1.0, 1.0, 0.05);
const glm::vec3 WALL_FRONT_TRANSLATION =	glm::vec3(0, 1, 0.95);
const glm::vec3 CEILING_SCALE =				glm::vec3(1.0, 0.05, 1.0);
const glm::vec3 CEILING_TRANSLATION =		glm::vec3(0, 1.95, 0);

#endif OBJECT_H


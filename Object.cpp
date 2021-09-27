#include "object.h"

Object::Object(const int type, int x, int y, int z) {
	this->type = type;
	scale = glm::vec3(SCALES[type][0], SCALES[type][1], SCALES[type][2]);
	translation = glm::vec3(TRANSLATIONS[type][0] + (x * 2), TRANSLATIONS[type][1] + (y * 2), TRANSLATIONS[type][2] + (z * 2));
	rotationAngle = ROTATIONS[type][0];
	rotation = glm::vec3(ROTATIONS[type][1], ROTATIONS[type][2], ROTATIONS[type][3]);
}

Object::Object() {}

void Object::draw(float r, float g, float b) {
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, translation);
	if (rotationAngle >= -5)
		M = glm::rotate(M, rotationAngle, rotation);
	M = glm::scale(M, scale);
	glUniform4f(sp->u("color"), r, g, b, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M)); //Za³aduj do programu cieniuj¹cego macierz modelu
	Models::cube.drawSolid(); //Narysuj obiekt
}
#include "object.h"

Object::Object(const int type, int x, int y, int z) {
	scale = glm::vec3(SCALES[type][0], SCALES[type][1], SCALES[type][2]);
	translation = glm::vec3(TRANSLATIONS[type][0] + (x * 2), TRANSLATIONS[type][1] + (y * 2), TRANSLATIONS[type][2] + (z * 2));
}

Object::Object() {}

void Object::draw(float r, float g, float b) {
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, translation);
	M = glm::scale(M, scale);
	glUniform4f(spLambert->u("color"), r, g, b, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M)); //Za³aduj do programu cieniuj¹cego macierz modelu
	Models::cube.drawSolid(); //Narysuj obiekt
}
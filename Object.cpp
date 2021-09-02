#include "object.h"

Object::Object(glm::vec3 s, glm::vec3 t) {
	scale = s;
	translation = t;
}

Object::Object() {
	scale = glm::vec3(0);
	translation = glm::vec3(0);
}

void Object::draw() {
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, translation);
	M = glm::scale(M, scale);
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M)); //Za³aduj do programu cieniuj¹cego macierz modelu
	Models::cube.drawSolid(); //Narysuj obiekt
}

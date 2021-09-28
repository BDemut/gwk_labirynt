#include "object.h"

Object::Object(const int type, int x, int y, int z) {
	this->type = type;
	scale = glm::vec3(SCALES[type][0], SCALES[type][1], SCALES[type][2]);
	translation = glm::vec3(TRANSLATIONS[type][0] + (x * 2), TRANSLATIONS[type][1] + (y * 2), TRANSLATIONS[type][2] + (z * 2));
	rotationAngle = ROTATIONS[type][0];
	rotation = glm::vec3(ROTATIONS[type][1], ROTATIONS[type][2], ROTATIONS[type][3]);
	if (type >= 1 && type <= 4)
		hitbox = HitBox(Models::cube.vertices, Models::cube.vertexCount, 0);
	if (type >= 6 && type <= 9)
		hitbox = HitBox(y, 3, type, glm::ivec3(x,y,z));
	if (type == 0)
		hitbox = HitBox(Models::cube.vertices, Models::cube.vertexCount, y, 1);
	if (type == 5)
		hitbox = HitBox(Models::cube.vertices, Models::cube.vertexCount, y, 2);
}

Object::Object() {}

glm::mat4 Object::getM()
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, translation);
	if (rotationAngle >= -5)
		M = glm::rotate(M, rotationAngle, rotation);
	M = glm::scale(M, scale);
	return M;
}

glm::mat4 Object::getRotationMatrix()
{
	glm::mat4 M = glm::mat4(1.0f);
	if (rotationAngle >= -5)
		M = glm::rotate(M, rotationAngle, rotation);
	return M;
}

glm::mat4 Object::getTMatrix()
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, translation);
	return M;
}

void Object::draw(float r, float g, float b) {
	glm::mat4 M = this->getM();
	glUniform4f(sp->u("color"), r, g, b, 1); //Ustaw kolor rysowania obiektu
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M)); //Za³aduj do programu cieniuj¹cego macierz modelu

	Models::cube.drawSolid(); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("texCoord0"));
}


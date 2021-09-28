/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "grid.h"
#include "HitBox.h"
#include "Collisions.h"

GLuint wallTex;

Grid grid = Grid();
HitBox camera = HitBox(-0.2f, 0.2f, -0.8f, 0.2f, -0.2f, 0.2f, 5);

float speed_x = 0; //[radiany/s]
float speed_y = 0; //[radiany/s]
float walk_speed = 0;

float kat_x = 0;

glm::vec3 pos = glm::vec3(0.0, 0.8, 0.0); //TODO: zamienić 0.8 na jakąś wysokość postaci
//glm::vec3 pos = glm::vec3(4.0, 0.8, 12.0); //TODO: zamienić 0.8 na jakąś wysokość postaci
glm::vec3 prevPos = glm::vec3(pos);

float aspectRatio = 1;

void calculateHeight(HitBox* obj, glm::ivec3 currentTile, float cameraDelta)
{
	int stepX = obj->hmXsize - 1;
	int stepZ = obj->hmZsize - 1;
	float tempXcoord = (1 + pos.x - 2 * currentTile.x) / 2;
	float tempZcoord = (1 + pos.z - 2 * currentTile.z) / 2;
	float tempX1val = obj->heightMap[(int)floor(stepX * tempXcoord)][(int)floor(stepZ * tempZcoord)] * fmod(stepX * tempXcoord, 1.0) +
		obj->heightMap[(int)ceil(stepX * tempXcoord)][(int)floor(stepZ * tempZcoord)] * (1 - fmod(stepX * tempXcoord, 1.0));
	float tempX2val = obj->heightMap[(int)floor(stepX * tempXcoord)][(int)ceil(stepZ * tempZcoord)] * fmod(stepX * tempXcoord, 1.0) +
		obj->heightMap[(int)ceil(stepX * tempXcoord)][(int)ceil(stepZ * tempZcoord)] * (1 - fmod(stepX * tempXcoord, 1.0));
	float height = tempX1val * fmod(stepZ * tempZcoord, 1.0) + tempX2val * (1 - fmod(stepZ * tempZcoord, 1.0));
	pos.y = height +  -1 *cameraDelta;
	//if (obj->hitboxType == 3) fprintf(stderr, "%f %f \n", pos.y, height);
}

void calculateHeightRamps(HitBox* obj, glm::ivec3 currentTile, float cameraDelta)
{
	float tempXcoord = (1 + pos.x - 2 * obj->tile.x) / 2;
	float tempZcoord = (1 + pos.z - 2 * obj->tile.z) / 2;
	float tempX1val = obj->heightMap[0][0] * fmod(tempXcoord, 1.0) +
		obj->heightMap[1][0] * (1 - fmod(tempXcoord, 1.0));
	float tempX2val = obj->heightMap[0][1] * fmod(tempXcoord, 1.0) +
		obj->heightMap[1][1] * (1 - fmod(tempXcoord, 1.0));
	float height = tempX1val * fmod(tempZcoord, 1.0) + tempX2val * (1 - fmod(tempZcoord, 1.0));
	pos.y = height + -1 * cameraDelta + 0.3;
	fprintf(stderr, "%f %f %f %f \n", pos.y, height, tempXcoord, tempZcoord);
	
}
void collisionAction(HitBox* obj1, HitBox* obj2, glm::ivec3 currentTile)
{
	if (obj1->hitboxType == 0 || obj2->hitboxType == 0)
	{
		pos = glm::vec3(prevPos);
	}
	else if (obj1->hitboxType == 3 || obj2->hitboxType == 3)
	{
		if (obj1->hitboxType == 3)
		{
			calculateHeightRamps(obj1, currentTile, camera.minY);
			fprintf(stderr, "Detected \n");
		}
		else if (obj2->hitboxType == 3)
		{
			calculateHeightRamps(obj2, currentTile, camera.minY);
			fprintf(stderr, "Detected \n");
		}
	}
	else if (obj1->hitboxType == 1 || obj2->hitboxType == 1)
	{
		if (obj1->hitboxType == 1)
		{
			calculateHeight(obj1, currentTile, camera.minY);
		}
		else if (obj2->hitboxType == 1)
		{
			calculateHeight(obj2, currentTile, camera.minY);
		}
	}
	else if (obj1->hitboxType == 2 || obj2->hitboxType == 2)
	{
		if (obj1->hitboxType == 2)
		{
			calculateHeight(obj1, currentTile, camera.maxY);
		}
		else if (obj2->hitboxType == 2)
		{
			calculateHeight(obj2, currentTile, camera.maxY);
		}
	}

}

glm::ivec3 currTile(glm::vec3 pos)
{
	float temp;
	int currTileX;
	int currTileY;
	int currTileZ;
	modf((pos.x + 1) / 2, &temp);
	currTileX = (int)temp;
	modf((pos.y) / 2, &temp);
	currTileY = (int)temp;
	modf((pos.z + 1) / 2, &temp);
	currTileZ = (int)temp;
	return glm::ivec3(currTileX, currTileY, currTileZ);
}

void checkForCollisions() 
{
	glm::ivec3 currentTile = currTile(pos);

	//fprintf(stderr, "X: %d Y: %d Z: %d \n", currentTile.x, currentTile.y, currentTile.z);

	int maxi = currentTile.x >= grid.x - 2 ? grid.x : currentTile.x + 2;
	int maxk = currentTile.z >= grid.z - 2 ? grid.z : currentTile.z + 2;

	for (int i = currentTile.x < 2 ? 0 : currentTile.x - 2; i < maxi; i++)
	{
		for (int j = 0; j < grid.y; j++)
		{
			for (int k = currentTile.z < 2 ? 0 : currentTile.z - 2; k < maxk; k++)
			{
				GridTile*** temp = grid.getTiles();
				std::vector<Object> temp2 = temp[i][j][k].objects;
				for (int l = 0; l < temp2.size(); l++)
				{
					if (temp2[l].hitbox.usable == false)
						continue;
					else
						if(Collisions::detectCollision(&camera, glm::translate(glm::mat4(1.0f), pos), &temp2[l].hitbox,
							temp2[l].hitbox.hitboxType == 3 ? temp2[l].getTMatrix() : temp2[l].getM()))
							collisionAction(&camera, &temp2[l].hitbox, currentTile);
				}
				temp2.clear();
			}
		}
	}
}

glm::vec3 calcDir(float kat_x, float kat_y) {
	glm::vec4 dir = glm::vec4(0, 0, 1, 0);
	glm::mat4 M = glm::rotate(glm::mat4(1.0f), kat_y, glm::vec3(0, 1, 0));
	M = glm::rotate(M, kat_x, glm::vec3(1, 0, 0));
	dir = M * dir;
	return glm::vec3(dir);
}

void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mod
) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_W) walk_speed = 2;
		if (key == GLFW_KEY_S) walk_speed = -2;
		if (key == GLFW_KEY_A) speed_y = 1;
		if (key == GLFW_KEY_D) speed_y = -1;
		if (key == GLFW_KEY_UP) speed_x = -1;
		if (key == GLFW_KEY_DOWN) speed_x = 1;
		if (key == GLFW_KEY_R) kat_x = 0; //Resetuje kąt patrzenia w górę i dół
		
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_A) speed_y = 0;
		if (key == GLFW_KEY_D) speed_y = 0;
		if (key == GLFW_KEY_W) walk_speed = 0;
		if (key == GLFW_KEY_S) walk_speed = 0;
		if (key == GLFW_KEY_UP) speed_x = 0;
		if (key == GLFW_KEY_DOWN) speed_x = 0;
	}
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    initShaders();
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0.2, 0.2, 0.2, 1); //Ustaw kolor czyszczenia bufora kolorów
	//glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, key_callback);
	wallTex = readTexture("wall.png");
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
	glDeleteTextures(1, &wallTex);
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window,float kat_x,float kat_y) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyść bufor koloru i bufor głębokości
	checkForCollisions();
	//fprintf(stderr, "X: %f Z: %f \n", pos.x, pos.z);

	glm::mat4 V = glm::lookAt(pos, pos+calcDir(kat_x,kat_y), glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), aspectRatio, 0.1f, 50.0f); //Wylicz macierz rzutowania

	sp->use(); //Aktywuj program cieniujący
	
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wallTex);

	grid.draw();

	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego
}

int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	float angle = 0; //zadeklaruj zmienną przechowującą aktualny kąt obrotu
	/*float*/ kat_x = 0;
	float kat_y = 0;
	glfwSetTime(0); //Wyzeruj licznik czasu
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		// Ograniczenie żeby patrzeć max 90 st w górę lub w dół
		kat_x = glm::clamp((float)(kat_x + speed_x * glfwGetTime()), -PI/2, PI/2);
		kat_y += speed_y * glfwGetTime();
		prevPos = glm::vec3(pos);
		pos += (float)(walk_speed * glfwGetTime()) * calcDir(kat_x, kat_y);
		glfwSetTime(0); //Wyzeruj licznik czasu
		drawScene(window,kat_x,kat_y); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}

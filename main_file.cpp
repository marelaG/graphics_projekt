/*
Niniejszy program jest wolnym oprogramowaniem; moĹźesz go
rozprowadzaÄ dalej i / lub modyfikowaÄ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez FundacjÄ Wolnego
Oprogramowania - wedĹug wersji 2 tej Licencji lub(wedĹug twojego
wyboru) ktĂłrejĹ z pĂłĹşniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziejÄ
, iĹź bÄdzie on
uĹźyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyĹlnej
gwarancji PRZYDATNOĹCI HANDLOWEJ albo PRZYDATNOĹCI DO OKREĹLONYCH
ZASTOSOWAĹ.W celu uzyskania bliĹźszych informacji siÄgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoĹciÄ
 wraz z niniejszym programem otrzymaĹeĹ teĹź egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeĹli nie - napisz do Free Software Foundation, Inc., 59 Temple
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
#include "lodepng.h"
#include "shaderprogram.h"
#include "GL/glu.h"
#include <vector>
#include "constants.h"

#include "floor.h"
#include "roof.h"
#include "bar.h"
#include "front.h"
#include "rectangle.h"
#include "model.h"



// Deklaracja nazw importowanych modeli 
Model* waza;
Model* waza2;
Model* wazaSerio;
Model* kamien;


float speed = PI; //Prędkość kątowa obrotu lewitujacego kameinia


// Parametry ustawienia kamery 
// Ustawienie pozycji kamery
glm::vec3 camera_position = glm::vec3(20.0f, 3.0f, -2.0f);
// Ustawianie kata patrzenia kamery
glm::vec3 camera_target = glm::vec3(-7.0f, 0.0f, 4.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 2.5f, 0.0f);

// Deklaracja nazw tekstur
GLuint wall, floorTex, column, bricks, roof, mozaika, water, fire, jar, gold;



ShaderProgram* sp;



//Procedura obslugi bledow
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}



	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
		
		// Zmiana pozycji kamery w zależności od naciśniętych klawiszy
		float camera_speed = 0.5f; // Predkosc poruszania
		float rotation_speed = 0.05f; // Predkosc zmiany kamery pov
		////////////////////////////////////////////////////////////////////////////////CIEZARY///////////////////////////////////////////////////////////////////////////////////
		glm::vec3 camera_direction = glm::normalize(camera_target - camera_position);
		glm::vec3 camera_right = glm::normalize(glm::cross(camera_direction, camera_up));


		// Jesli cos jest wcisniete wystarczajaco dlugo
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			if (key == GLFW_KEY_W) {
				// czyli idiemy w przod
				camera_position += camera_speed * camera_direction;
				camera_target += camera_speed * camera_direction;
				camera_position.y = 2.0f;
			}
			else if (key == GLFW_KEY_S) {
				camera_position -= camera_speed * camera_direction;
				camera_target -= camera_speed * camera_direction;
				camera_position.y = 2.0f;
			}
			else if (key == GLFW_KEY_A) {
				camera_position -= camera_speed * camera_right;
				camera_target -= camera_speed * camera_right;
				camera_position.y = 2.0f;
			}
			else if (key == GLFW_KEY_D) {
				camera_position += camera_speed * camera_right;
				camera_target += camera_speed * camera_right;
				camera_position.y = 2.0f;
			}
			else if (key == GLFW_KEY_UP) {

				glm::quat rotation = glm::angleAxis(rotation_speed, camera_right);
				glm::vec3 new_direction = rotation * (camera_target - camera_position);
				camera_target = camera_position + new_direction;
				//camera_position.y = 5;
			}
			else if (key == GLFW_KEY_DOWN) {
				glm::quat rotation = glm::angleAxis(-rotation_speed, camera_right);
				glm::vec3 new_direction = rotation * (camera_target - camera_position);
				camera_target = camera_position + new_direction;
				//camera_position.y = 5;
			}

			
			else if (key == GLFW_KEY_LEFT) {
				glm::quat rotation = glm::angleAxis(rotation_speed, camera_up);
				camera_direction = glm::normalize(rotation * camera_direction);
				camera_target = camera_position + camera_direction;
			}
			else if (key == GLFW_KEY_RIGHT) {
				glm::quat rotation = glm::angleAxis(-rotation_speed, camera_up);
				camera_direction = glm::normalize(rotation * camera_direction);
				camera_target = camera_position + camera_direction;
			}
			
			// Aktualizacja macierzy widoku
			glm::mat4 V = glm::lookAt(camera_position, camera_target, camera_up);

		}
	}




GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamieci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do ktołrych wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamieci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt


	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamieci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S,
		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T,
		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);

	return tex;
}

//Procedura inicjujÄca
void initOpenGLProgram(GLFWwindow* window) {

	//************Tutaj umieszczaj kod, ktory nalezy wykonac raz na poczatku************
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorow
	glEnable(GL_DEPTH_TEST); //WĹacz test glebokosci na pikselach
	glfwSetKeyCallback(window, key_callback);


	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	
	// Read tekstury i modele

	roof = readTexture("dach.png");
	floorTex = readTexture("floor.png");
	column = readTexture("column1.png");
	bricks = readTexture("bricks.png");
	mozaika = readTexture("mozaika.png");
	wall = readTexture("wall.png");
	water = readTexture("water.png");
	fire = readTexture("fire.png");
	gold = readTexture("gold.png");
	waza = new Model("stone.obj", "column1.png");
	waza2 = new Model("stone.obj", "fire.png");
	kamien = new Model("stone.obj", "gold.png");
	wazaSerio = new Model("jar.obj", "Ancient_jar_diffuse.png");




}




//Zwolnienie zasobow zajetych przez program
void freeOpenGLProgram(GLFWwindow* window) {

	//************Tutaj umieszczaj kod, ktory naleĹźy wykonac po zakoĹczeniu petli glownej************
	delete sp;
	delete waza;
	delete waza2;
	delete wazaSerio;
	delete kamien;
}

void drawBar(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(sp->a("vertex"));
	glEnableVertexAttribArray(sp->a("texCoord"));

	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 5 * sizeof(GLfloat), barVertices);
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 5 * sizeof(GLfloat), barVertices + 3);


	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, barNormals);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, column); // Bind the column texture BYLO TEX
	glUniform1i(sp->u("column"), 0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, barIndices);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));
}
void drawWall(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(sp->a("vertex"));
	glEnableVertexAttribArray(sp->a("texCoord"));

	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 5 * sizeof(GLfloat), barVertices);
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 5 * sizeof(GLfloat), barVertices + 3);


	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, barNormals);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wall); // Bind the column texture BYLO TEX
	glUniform1i(sp->u("wall"), 0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, barIndices);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));
}
void drawSteps(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(sp->a("vertex"));
	glEnableVertexAttribArray(sp->a("texCoord"));

	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 5 * sizeof(GLfloat), barVertices);
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 5 * sizeof(GLfloat), barVertices + 3);


	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, barNormals);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTex); // Bind the column texture BYLO TEX
	glUniform1i(sp->u("floor"), 0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, barIndices);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));
}





void texCylinder(glm::mat4 P, glm::mat4 V, glm::mat4 M, int sides) {
	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, column);
	glUniform1i(sp->u("column"), 0);
	// Generate vertices for the cylinder
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texCoords;

	GLfloat radius = 1.0f;
	GLfloat height = 3.0f;

	for (int i = 0; i <= sides; ++i) { // Note: Use <= to close the cylinder
		float theta = 2.0f * glm::pi<float>() * i / sides;
		float x = radius * cos(theta);
		float z = radius * sin(theta);
		float u = static_cast<float>(i) / sides; // Horizontal texture coordinate

		// Bottom vertex
		vertices.push_back(x);
		vertices.push_back(0.0f);
		vertices.push_back(z);
		texCoords.push_back(u);
		texCoords.push_back(0.0f); // Bottom vertex v coordinate

		// Top vertex
		vertices.push_back(x);
		vertices.push_back(height);
		vertices.push_back(z);
		texCoords.push_back(u);
		texCoords.push_back(1.0f); // Top vertex v coordinate
	}
	std::vector<GLfloat> normals;

	for (int i = 0; i <= sides; ++i) {
		float theta = 2.0f * glm::pi<float>() * i / sides;
		float nx = cos(theta);
		float ny = 0.0f; // Normal along the y-axis is 0 for a cylinder
		float nz = sin(theta);

		// Push the normals for both bottom and top vertices
		normals.push_back(nx);
		normals.push_back(ny);
		normals.push_back(nz);
		normals.push_back(nx);
		normals.push_back(ny);
		normals.push_back(nz);
	}

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, normals.data());


	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, vertices.data());

	glEnableVertexAttribArray(sp->a("texCoord"));
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());

	glDrawArrays(GL_TRIANGLE_STRIP, 0, (sides + 1) * 2); // Adjusted to (sides + 1) * 2

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
}

void texRoof(glm::mat4 P, glm::mat4 V, glm::mat4 M) {


	M = glm::scale(M, glm::vec3(5.0f, 2.0f, 3.8)); // Skalowanie dachu wzdĹuĹź osi x, y i z odpowiednio
	M = glm::translate(M, glm::vec3(1.0f, 2.5f, 0.0f));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	sp->use(); //Aktywuj program cieniujÄ


		glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P)); //ZaĹaduj do programu cieniujÄcego macierz rzutowania
		glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V)); //ZaĹaduj do programu cieniujÄcego macierz widoku
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M)); //ZaĹaduj do programu cieniujÄcego macierz modelu


		glEnableVertexAttribArray(sp->a("vertex"));  //WĹÄcz przesyĹanie danych do atrybutu vertex
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, roofVertices); //WskaĹź tablicÄ z danymi dla atrybutu vertex



	glEnableVertexAttribArray(sp->a("normal"));  //WĹÄcz przesyĹanie danych do atrybutu normal
		glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, roofNormals); //WskaĹź tablicÄ z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord"));  //WĹÄcz przesyĹanie danych do atrybutu texCoord0
		glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, roofTexCoords); //WskaĹź tablicÄ z danymi dla atrybutu texCoord0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roof);
	glUniform1i(sp->u("roof"), 0);


	glDrawArrays(GL_TRIANGLES, 0, roofVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));



}



// Procedura rysujÄca zawartoĹÄ sceny
void drawScene(GLFWwindow* window, float angle) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // WyczyĹÄ bufor koloru i bufor gĹÄbokoĹci

	glm::mat4 M = glm::mat4(1.0f); // Zainicjuj macierz modelu macierzÄjednostkowÄ

	
	glm::mat4 V = glm::lookAt(camera_position, camera_target, camera_up);
	
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); // Wylicz macierz rzutowania

	//glUniform4f(sp->u("lp"), 0, 0, -6, 1);

	// Dach
	M = glm::mat4(1.0f);
	texRoof(P, V, M);
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));


	// Podstawy i schody
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 7.65f));
	M = glm::translate(M, glm::vec3(0.0f, 8.5f, 0.0f));
	drawSteps(P, V, M); // Zamiast texFloor

	// Najmniejsza podstawa
	M = glm::translate(M, glm::vec3(0.0f, -10.0f, 0.0f));
	drawSteps(P, V, M); // Zamiast texFloor

	// Srodkowa podstawa
	M = glm::scale(M, glm::vec3(1.2f, 1.0f, 1.2f));
	M = glm::translate(M, glm::vec3(0.0f, -0.5f, 0.0f));
	drawSteps(P, V, M);

	// Najwieksza podstawa
	M = glm::scale(M, glm::vec3(1.1f, 1.0f, 1.1f));
	M = glm::translate(M, glm::vec3(0.0f, -0.5f, 0.0f));
	drawSteps(P, V, M);


	//-------"Kaplica--"---------
	// Boczna Sciana kaplicy 1
	M = glm::mat4(1.0f);

	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.3f));
	M = glm::scale(M, glm::vec3(0.5f, 12.8, 0.6f));
	M = glm::translate(M, glm::vec3(2.5f, -1.0f, -6.0f));

	drawWall(P, V, M);


	//boczna sciana kaplicy 2
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 12.0f));
	drawWall(P, V, M);


	//tylna sciana kaplicy 3
	M = glm::translate(M, glm::vec3(9.7f, 0.0f, -5.5f));
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 0.6f));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	drawWall(P, V, M);



//--------CzÄĹÄ odpowiadajÄca z a rysownia kolum i o poprzeczek
	int numColumns = 5;
	int numRows = 2;
	float spacing_rows = 11.2f;
	float spacing_columns = 3.2f;

	for (int i = 0; i < numColumns; ++i) {
		for (int j = 0; j < numRows; ++j) {
			glm::mat4 M = glm::mat4(1.0f);
			M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
			M = glm::translate(M, glm::vec3(i * spacing_columns - (numColumns - 1) * spacing_columns / 2, 0.0f, j * spacing_rows - (numRows - 1) * spacing_rows / 2));
			M = glm::scale(M, glm::vec3(0.5f, 3.0f, 0.5f));
			texCylinder(P, V, M, 20);
		}
	}

	// Poprzeczki nad kolumnami wzdĹuĹź
	for (int j = 0; j < numRows; ++j) {
		glm::mat4 M = glm::mat4(1.0f);
		M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
		M = glm::translate(M, glm::vec3(0.0f, 6.5f, j * spacing_rows - (numRows - 1) * spacing_rows / 2)); // Lower the bar a bit (from 9.0f to 8.5f)
		M = glm::scale(M, glm::vec3(numColumns * spacing_columns * 0.05f, 2.0f, 1.0f)); // Adjust the length scale to make the bar shorter
		drawBar(P, V, M); // Draw the bar
	}

	// Kolumny wszerz
	numColumns = 4;
	numRows = 2;
	spacing_rows = 18.0f; // Distance between columns
	spacing_columns = 3.3f;
	for (int i = 0; i < numColumns; ++i) {
		for (int j = 0; j < numRows; ++j) {
			glm::mat4 M = glm::mat4(1.0f);
			M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
			M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // ObrĂłt wokĂłĹ osi Y, Ĺźeby byĹo wszerz
			M = glm::translate(M, glm::vec3(i * spacing_columns - (numColumns - 1) * spacing_columns / 2, 0.0f, j * spacing_rows - (numRows - 1) * spacing_rows / 2));
			M = glm::scale(M, glm::vec3(0.5f, 3.0f, 0.5f)); // Adjust scale to fit the columns
			texCylinder(P, V, M, 20); // Draw the cylinder
			M = glm::rotate(M, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	// Poprzeczki wszerz
	for (int j = 0; j < numRows; ++j) {
		glm::mat4 M = glm::mat4(1.0f);
		M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
		M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		M = glm::translate(M, glm::vec3(0.0f, 6.5f, j * spacing_rows - (numRows - 1) * spacing_rows / 2)); // Lower the bar a bit (from 9.0f to 8.5f)
		M = glm::scale(M, glm::vec3(numColumns * spacing_columns * 0.05f, 2.0f, 1.0f)); // Adjust the length scale to make the bar shorter
		drawBar(P, V, M); // Draw the bar
		M = glm::rotate(M, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}


	//---------------------Procedura rysujÄca kamienie - obieky poruszajÄce siÄ niezaleĹźnie------------------
	glm::mat4 P1 = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);
	glm::mat4 V1 = glm::lookAt(camera_position, camera_target, camera_up);
	glm::mat4 M1 = glm::mat4(1.0f);
	M1 = glm::scale(M1, glm::vec3(0.7f, 0.7f, 0.7f));
	M1 = glm::translate(M1, glm::vec3(7.0f, 0.0f, 5.0f));

	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, GL_FALSE, glm::value_ptr(P1));
	glUniformMatrix4fv(sp->u("V"), 1, GL_FALSE, glm::value_ptr(V1));
	glUniformMatrix4fv(sp->u("M"), 1, GL_FALSE, glm::value_ptr(M1));
	waza->draw(sp);

	M1 = glm::scale(M1, glm::vec3(0.3f, 0.3f, 0.3f));
	M1 = glm::translate(M1, glm::vec3(3.0f, -1.0f, 3.0f));
	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, GL_FALSE, glm::value_ptr(P1));
	glUniformMatrix4fv(sp->u("V"), 1, GL_FALSE, glm::value_ptr(V1));
	glUniformMatrix4fv(sp->u("M"), 1, GL_FALSE, glm::value_ptr(M1));
	waza->draw(sp);

	M1 = glm::translate(M1, glm::vec3(0.0f, 1.0f, -42.0f));
	M1 = glm::scale(M1, glm::vec3(0.07f, 0.07f, 0.07f));
	

	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, GL_FALSE, glm::value_ptr(P1));
	glUniformMatrix4fv(sp->u("V"), 1, GL_FALSE, glm::value_ptr(V1));
	glUniformMatrix4fv(sp->u("M"), 1, GL_FALSE, glm::value_ptr(M1));
	wazaSerio->draw(sp);
	
	////////////////////////////////latajacy kamien///////////////////////////
	glm::mat4 P2 = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);
	glm::mat4 V2 = glm::lookAt(camera_position, camera_target, camera_up);
	glm::mat4 M2 = glm::mat4(1.0f);
	M2 = glm::scale(M2, glm::vec3(0.4f, 0.4f, 0.4f));
	M2 = glm::translate(M2, glm::vec3(7.0f, 10.0f, 0.0f));
	M2 = glm::rotate(M2, angle, glm::vec3(0.0f, 1.0f, 0.0f)); //Macierz planety to macierz słońca pomnożona razy macierz obrotu

	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, GL_FALSE, glm::value_ptr(P2));
	glUniformMatrix4fv(sp->u("V"), 1, GL_FALSE, glm::value_ptr(V2));
	glUniformMatrix4fv(sp->u("M"), 1, GL_FALSE, glm::value_ptr(M2));
	kamien->draw(sp);


	glfwSwapBuffers(window); //Skopiuj bufor tylny do bufora przedniego

}


int main(void)
{
	GLFWwindow* window; //WskaĹşnik na obiekt reprezentujÄcy okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurÄ obsĹugi bĹÄdĂłw

	if (!glfwInit()) { //Zainicjuj bibliotekÄ GLFW
		fprintf(stderr, "Nie moĹźna zainicjowaÄ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);  //UtwĂłrz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //JeĹźeli okna nie udaĹo siÄ utworzyÄ, to zamknij program
	{
		fprintf(stderr, "Nie moĹźna utworzyÄ okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siÄ aktywny i polecenia OpenGL bÄdÄdotyczyÄ wĹaĹnie jego.
		glfwSwapInterval(1); //Czekaj na 1 powrĂłt plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekÄ GLEW
		fprintf(stderr, "Nie moĹźna zainicjowaÄ GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujÄce
	float angle = 0; //Aktualny kąt obrotu obiektu
	glfwSetTime(0); //Wyzeruj timer
	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle += speed * glfwGetTime(); //Oblicz przyrost kąta po obrocie
		glfwSetTime(0); //Wyzeruj timer
		drawScene(window, angle); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //UsuĹ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajÄte przez GLFW
	exit(EXIT_SUCCESS);
}
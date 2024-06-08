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


#include "floor.h"
#include "roof.h"
#include "bar.h"
#include "front.h"
#include "rectangle.h"
#include "model.h"

#include "constants.h"

#include "lodepng.h"
#include "shaderprogram.h"
#include "GL/glu.h"
#include <vector>
Model* waza;
Model* waza2;
float speed_x = 0;//[radiany/s]
float speed_y = 0;//[radiany/s]

glm::vec3 camera_position = glm::vec3(5.0f, 3.0f, -15.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 2.5f, 0.0f);

GLuint wall, floorTex, column, bricks, roof, mozaika,water, fire;



ShaderProgram* sp;


float aspectRatio = 1;


//Odkomentuj, żeby rysować czajnik
float* normals = frontNormals;
float* vertices = frontVertices;
float* texCoords = frontTexCoords;

int vertexCount = frontVertexCount;
float elapsedTime = 0.0f;
bool up = false;
int count = 0; 


//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}




void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	// Zmiana pozycji kamery w zależności od naciśniętych klawiszy
	float camera_speed = 0.5f;
	if (key == GLFW_KEY_W) {
		camera_position += camera_speed * glm::normalize(camera_target - camera_position);
	}
	else if (key == GLFW_KEY_S) {
		camera_position -= camera_speed * glm::normalize(camera_target - camera_position);
	}
	else if (key == GLFW_KEY_A) {
		camera_position -= glm::normalize(glm::cross(camera_target - camera_position, camera_up)) * camera_speed;
	}
	else if (key == GLFW_KEY_D) {
		camera_position += glm::normalize(glm::cross(camera_target - camera_position, camera_up)) * camera_speed;
	}
	else if (key == GLFW_KEY_O) {
		camera_position += camera_up * camera_speed;
	}

	else if (key == GLFW_KEY_K) {
		camera_position -= camera_up * camera_speed;
	}


	// Aktualizacja macierzy widoku
	glm::mat4 V = glm::lookAt(camera_position, camera_target, camera_up);
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


	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
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

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {

	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia bufora kolorów
	glEnable(GL_DEPTH_TEST); //Włącz test głębokości na pikselach
	glfwSetKeyCallback(window, key_callback);


	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");

	roof = readTexture("dach.png");
	floorTex = readTexture("floor.png");
	column = readTexture("column1.png");
	bricks = readTexture("bricks.png");
	mozaika = readTexture("mozaika.png");
	wall = readTexture("wall.png");
	water = readTexture("water.png");
	fire = readTexture("fire.png");
	waza = new Model("stone.obj", "column1.png");
	waza2 = new Model("stone.obj", "fire.png");



}




//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {

	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
	glDeleteTextures(1, &roof);
	delete sp;
	delete waza;
	delete waza2;
}
void updateElapsedTime() {
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    elapsedTime += static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;
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




// Function to generate a sphere's vertices, normals, and indices
#include <vector>

// Function to generate a sphere's vertices, normals, and indices
void generateSphere(float radius, int stacks, int slices, std::vector<float>& vertices, std::vector<float>& normals, std::vector<unsigned int>& indices) {
	for (int i = 0; i <= stacks; ++i) {
		float V = (float)i / stacks;
		float phi = V * glm::pi<float>();

		for (int j = 0; j <= slices; ++j) {
			float U = (float)j / slices;
			float theta = U * (glm::pi<float>() * 2);

			float x = cos(theta) * sin(phi);
			float y = cos(phi);
			float z = sin(theta) * sin(phi);

			vertices.push_back(x * radius);
			vertices.push_back(y * radius);
			vertices.push_back(z * radius);

			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		}
	}

	for (int i = 0; i < slices * stacks + slices; ++i) {
		indices.push_back(i);
		indices.push_back(i + slices + 1);
		indices.push_back(i + slices);

		indices.push_back(i + slices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
}


void drawRectangle(glm::mat4 P, glm::mat4 V, glm::mat4 M) {


	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(sp->a("vertex"));
	glEnableVertexAttribArray(sp->a("texCoord"));

	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0,  rectangleVertices);
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false,0,  rectangleVertices);


	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, rectangleNormals);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roof); // Bind the column texture BYLO TEX
	glUniform1i(sp->u("roof"), 0);

	glDrawArrays(GL_TRIANGLES, 0, rectangleVertexCount);

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


void texFloor(glm::mat4 P, glm::mat4 V, glm::mat4 M) {



	sp->use(); //Aktywuj program cieniujący

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu


	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, floorVertices); //Wskaż tablicę z danymi dla atrybutu vertex



	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, floorNormals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord"));  //Włącz przesyłanie danych do atrybutu texCoord0
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, floorTexCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTex);
	glUniform1i(sp->u("floorTex"), 0);


	glDrawArrays(GL_TRIANGLES, 0, floorVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));
}


void texFront(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	M = glm::translate(M, glm::vec3(-10.0f, 10.5f, 0.0f));
	M = glm::scale(M, glm::vec3(10.0f, 4.0f, 6.65f)); // Skalowanie dachu wzdłuż osi x, y i z odpowiednio

	sp->use(); //Aktywuj program cieniujący

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu


	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, frontVertices); //Wskaż tablicę z danymi dla atrybutu vertex



	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, frontNormals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord"));  //Włącz przesyłanie danych do atrybutu texCoord0
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, frontTexCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mozaika);
	glUniform1i(sp->u("mozaika"), 0);


	glDrawArrays(GL_TRIANGLES, 0, frontVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));
}


void texWall(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	M = glm::scale(M, glm::vec3(1.0f, 1.5f, 0.4f));
	M = glm::translate(M, glm::vec3(0.0f, 4.0f, 0.0f));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	sp->use(); //Aktywuj program cieniujący

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu


	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, floorVertices); //Wskaż tablicę z danymi dla atrybutu vertex



	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, floorNormals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord"));  //Włącz przesyłanie danych do atrybutu texCoord0
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, floorTexCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wall);
	glUniform1i(sp->u("wall"), 0);


	glDrawArrays(GL_TRIANGLES, 0, floorVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));
}


void texRoof(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

	M = glm::translate(M, glm::vec3(-10.0f, 10.5f, 0.0f));
	M = glm::scale(M, glm::vec3(10.0f, 4.0f, 6.65f)); // Skalowanie dachu wzdłuż osi x, y i z odpowiednio

	sp->use(); //Aktywuj program cieniujący

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P)); //Załaduj do programu cieniującego macierz rzutowania
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V)); //Załaduj do programu cieniującego macierz widoku
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M)); //Załaduj do programu cieniującego macierz modelu


	glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, roofVertices); //Wskaż tablicę z danymi dla atrybutu vertex



	glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, roofNormals); //Wskaż tablicę z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord"));  //Włącz przesyłanie danych do atrybutu texCoord0
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, roofTexCoords); //Wskaż tablicę z danymi dla atrybutu texCoord0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roof);
	glUniform1i(sp->u("roof"), 0);


	glDrawArrays(GL_TRIANGLES, 0, roofVertexCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));
	glDisableVertexAttribArray(sp->a("normal"));



}
void drawSphere(glm::mat4 P, glm::mat4 V, glm::mat4 M, GLuint texture) {
	static std::vector<float> vertices;
	static std::vector<float> normals;
	static std::vector<unsigned int> indices;
	static GLuint VBO, VAO, EBO;
	static bool initialized = false;

	if (!initialized) {
		generateSphere(1.0f, 20, 20, vertices, normals, indices);

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(sp->a("vertex"));
		glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(sp->a("normal"));
		glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(vertices.size() * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		initialized = true;
	}

	sp->use();

	glUniformMatrix4fv(sp->u("P"), 1, GL_FALSE, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, GL_FALSE, glm::value_ptr(M));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(sp->u("texture0"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}




// Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Wyczyść bufor koloru i bufor głębokości

	glm::mat4 M = glm::mat4(1.0f); // Zainicjuj macierz modelu macierzą jednostkową
	// M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f)); // Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y
	// M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f)); // Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi X
	glm::mat4 V = glm::lookAt(camera_position, camera_target, camera_up);
	// glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Wylicz macierz widoku
	glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); // Wylicz macierz rzutowania

	glUniform4f(sp->u("lp"), 0, 0, -6, 1);


	// Kolumny wzdłuż
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

	// Poprzeczki nad kolumnami wzdłuż
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
			M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Obrót wokół osi Y, żeby było wszerz
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

	// Dach
	M = glm::mat4(1.0f);



	//texRoof(P, V, M);
	//M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0.1f));
	M = glm::scale(M, glm::vec3(5.2f, 1.5f, 3.5f));
	M = glm::translate(M, glm::vec3(0.0f, 4.0f, 0.2f));
	M = glm::rotate(M, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // ObrĂłt wokĂłĹ osi Y, Ĺźeby byĹo wszerz
	drawRectangle(P, V, M);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, -0.5f));
	M = glm::rotate(M, glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // ObrĂłt wokĂłĹ osi Y, Ĺźeby byĹo wszerz

	drawRectangle(P, V, M);

	//M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0.1f));
	//M = glm::translate(M, glm::vec3(0.0f, -4.0f, 1.0f));
	//M = glm::rotate(M, glm::radians(150.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // Obrót wokół osi Y, żeby było wszerz

	M = glm::mat4(1.0f);
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

	// Mozaiki na frontach
	texFront(P, V, M);

	// Podstawy i schody
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 7.65f));
	M = glm::translate(M, glm::vec3(0.0f, 8.5f, 0.0f));
	drawSteps(P, V, M); // Zamiast texFloor

	// Najmniejsza podstawa
	M = glm::translate(M, glm::vec3(0.0f, -10.0f, 0.0f));
	drawSteps(P, V, M); // Zamiast texFloor

	// Środkowa podstawa
	M = glm::scale(M, glm::vec3(1.2f, 1.0f, 1.2f));
	M = glm::translate(M, glm::vec3(0.0f, -1.0f, 0.0f));
	drawSteps(P, V, M); // Zamiast texFloor

	// Największa podstawa
	M = glm::scale(M, glm::vec3(1.1f, 1.0f, 1.1f));
	M = glm::translate(M, glm::vec3(0.0f, -1.0f, 0.0f));
	drawSteps(P, V, M); // Zamiast texFloor



	// Boczna ściana kaplicy
	M = glm::mat4(1.0f);
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
	M = glm::scale(M, glm::vec3(0.5f, 12.8, 0.6f));
	M = glm::translate(M, glm::vec3(2.5f, -1.0f, -3.0f));
	drawWall(P, V, M);


	//boczna sciana kaplicy
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 6.0f));
	drawWall(P, V, M);


	//tylna sciana kaplicy
	M = glm::translate(M, glm::vec3(9.7f, 0.0f, -3.0f));
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 0.38f));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	drawWall(P, V, M);

	//M = glm::rotate(M, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // przywracanie macierzy w "centrum"
	M = glm::translate(M, glm::vec3(-4.0f, 0.0f, -10.0f));

	M = glm::scale(M, glm::vec3(0.3f, 1.0f, 0.8f));

	drawWall(P, V, M);

	M = glm::translate(M, glm::vec3(27.0f, 0.0f, 0.0f));
	drawWall(P, V, M);



	M = glm::scale(M, glm::vec3(1.8f, 0.7f, 1.0f));
	M = glm::translate(M, glm::vec3(-7.5f, 7.4f, 0.0f));
	//drawWall(P, V, M);

	/*
	glm::mat4 P1 = glm::perspective(glm::radians(50.0f), aspectRatio, 1.0f, 50.0f);
	glm::mat4 V1 = glm::lookAt(camera_position, camera_target, camera_up);
	glm::mat4 M1 = glm::mat4(1.0f);
	glm::mat4 sphereModel = glm::translate(M1, glm::vec3(0.0f, 5.0f, 0.0f)); // Adjust the position as needed
	if (up = false) {
		drawSphere(P1, V1, sphereModel, water); // Use an appropriate texture
		up = true;
	}
	else {
	sphereModel = glm::translate(M1, glm::vec3(0.0f, 4.5f, 0.0f)); // Adjust the position as needed
	drawSphere(P1, V1, sphereModel, fire); // Use an appropriate texture
	up = false;
}*/
/*	if (up = false) {
		count += 1;
		if (count = 5000) {
			glm::mat4 sphereModel = glm::translate(M1, glm::vec3(0.0f, 5.0f, 0.0f)); // Adjust the position as needed
			drawSphere(P1, V1, sphereModel, water); // Use an appropriate texture
			up = true;
			count = 0;
		}
	}
	else {
		count += 1;
		if (count = 5000) {
			// Example: Drawing a floating sphere
			sphereModel = glm::translate(M1, glm::vec3(0.0f, 4.5f, 0.0f)); // Adjust the position as needed
			drawSphere(P1, V1, sphereModel, water);
			up = false;
			count = 0;
		}
	}*/
	


	
	//torus niezalezny 
//	glm::mat4 P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	//glm::mat4 V = glm::lookAt(
		//glm::vec3(0.0f, 0.0f, 5.0f), // Camera position
		//glm::vec3(0.0f, 0.0f, 0.0f), // Look at point
		//glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
	//);
	//glm::mat4 M = glm::mat4(1.0f); // Identity matrix
	//M = glm::translate(M, glm::vec3(0.0f, 1.0f, 0.0f)); // Translate the torus up by 1 units


	//Models::torus.drawSolid();

	glm::mat4 P1 = glm::perspective(glm::radians(50.0f), aspectRatio, 1.0f, 50.0f);
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

	window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

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

	// Główna pętla
	glfwSetTime(0); //Wyzeruj licznik czasu
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		// Nie potrzebujemy już zmiennej angle_x i angle_y
		glfwSetTime(0); //Wyzeruj licznik czasu
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}

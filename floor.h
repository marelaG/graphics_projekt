#pragma once
#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED

int floorVertexCount = 36;

float floorTexCoords[] = {
	// Œciana przednia
	10.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// Œciana tylna
	10.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// Œciana lewa
	8.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	8.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// Œciana prawa
	8.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	8.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// Œciana górna
	10.0f, 0.0f,  0.0f, 8.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 8.0f,  0.0f, 8.0f,

	// Œciana dolna
	10.0f, 0.0f,  0.0f, 8.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 8.0f,  0.0f, 8.0f,
};

float floorVertices[] = {
	// Œciana przednia (x, y, z) - ok

		5.0f, 1.0f, 4.0f, 1.0f,   // F
		-5.0f, 1.0f, 4.0f, 1.0f,  // E
		-5.0f, 0.0f, 4.0f, 1.0f,  // A





	5.0f, 1.0f, 4.0f, 1.0f,   // F
	5.0f, 0.0f, 4.0f, 1.0f,   // B
	-5.0f, 0.0f, 4.0f, 1.0f,  // A



	// Œciana tylna -ok
	-5.0f, 1.0f, -4.0f, 1.0f, // H
		5.0f, 1.0f, -4.0f, 1.0f,  // G
			5.0f, 0.0f, -4.0f, 1.0f,  // D

	-5.0f, 0.0f, -4.0f, 1.0f, // C
	-5.0f, 1.0f, -4.0f, 1.0f, // H
	5.0f, 0.0f, -4.0f, 1.0f,  // D

	// Œciana lewa - ok
	-5.0f, 1.0f, -4.0f, 1.0f, // H
	-5.0f, 0.0f, 4.0f, 1.0f,  // A
	-5.0f, 1.0f, 4.0f, 1.0f,  // E


	-5.0f, 1.0f, -4.0f, 1.0f, // H
	-5.0f, 0.0f, -4.0f, 1.0f, // C
	-5.0f, 0.0f, 4.0f, 1.0f,  // A




	// Œciana prawa - o
	5.0f, 1.0f, -4.0f, 1.0f,  // G
	5.0f, 0.0f, 4.0f, 1.0f,   // B
	5.0f, 1.0f, 4.0f, 1.0f,   // F


	5.0f, 1.0f, -4.0f, 1.0f,  // G
	5.0f, 0.0f, -4.0f, 1.0f,  // D
	5.0f, 0.0f, 4.0f, 1.0f,   // B


	// Œciana górna -ok
	-5.0f, 1.0f, 4.0f, 1.0f,  // E
	5.0f, 1.0f, -4.0f, 1.0f,  // G
	5.0f, 1.0f, 4.0f, 1.0f,   // F


	-5.0f, 1.0f, 4.0f, 1.0f,  // E
	-5.0f, 1.0f, -4.0f, 1.0f, // H
	5.0f, 1.0f, -4.0f, 1.0f,  // G

	// Œciana dolna - ok

	-5.0f, 0.0f, 4.0f, 1.0f,  // A
	5.0f, 0.0f, -4.0f, 1.0f,  // D
	5.0f, 0.0f, 4.0f, 1.0f,   // B

	-5.0f, 0.0f, 4.0f, 1.0f,  // A
	-5.0f, 0.0f, -4.0f, 1.0f, // C
	5.0f, 0.0f, -4.0f, 1.0f,  // D
};




float floorNormals[] = {
    // Normals for Œciana przednia
    0.0f, 0.0f, -1.0f,  // F
    0.0f, 0.0f, -1.0f,  // E
    0.0f, 0.0f, -1.0f,  // A

    0.0f, -1.0f, 0.0f,  // F
    0.0f, -1.0f, 0.0f,  // B
    0.0f, -1.0f, 0.0f,  // A

    // Normals for Œciana tylna
    0.0f, 0.0f, 1.0f,  // H
    0.0f, 0.0f, 1.0f,  // G
    0.0f, 0.0f, 1.0f,  // D

    0.0f, 1.0f, 0.0f,  // C
    0.0f, 1.0f, 0.0f,  // H
    0.0f, 1.0f, 0.0f,  // D

    // Normals for Œciana lewa
    1.0f, 0.0f, 0.0f,  // H
    1.0f, 0.0f, 0.0f,  // A
    1.0f, 0.0f, 0.0f,  // E

    0.0f, 1.0f, 0.0f,  // H
    0.0f, 1.0f, 0.0f,  // C
    0.0f, 1.0f, 0.0f,  // A

    // Normals for Œciana prawa
    -1.0f, 0.0f, 0.0f,  // G
    -1.0f, 0.0f, 0.0f,  // B
    -1.0f, 0.0f, 0.0f,  // F

    0.0f, -1.0f, 0.0f,  // G
    0.0f, -1.0f, 0.0f,  // D
    0.0f, -1.0f, 0.0f,  // B

    // Normals for Œciana górna
    1.0f, 0.0f, 0.0f,  // E
    1.0f, 0.0f, 0.0f,  // G
    1.0f, 0.0f, 0.0f,  // F

    0.0f, -1.0f, 0.0f,  // E
    0.0f, -1.0f, 0.0f,  // H
    0.0f, -1.0f, 0.0f,  // G

    // Normals for Œciana dolna
    0.0f, -1.0f, 0.0f,  // A
    0.0f, -1.0f, 0.0f,  // D
    0.0f, -1.0f, 0.0f,  // B

    0.0f, 1.0f, 0.0f,  // A
    0.0f, 1.0f, 0.0f,  // C
    0.0f, 1.0f, 0.0f,  // D
};

#endif // FLOOR_H_INCLUDED

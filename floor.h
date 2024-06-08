#pragma once
#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED

int floorVertexCount = 36;

float floorTexCoords[] = {
	// �ciana przednia
	10.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// �ciana tylna
	10.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// �ciana lewa
	8.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	8.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// �ciana prawa
	8.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	8.0f, 0.0f,  10.0f, 1.0f,  0.0f, 1.0f,

	// �ciana g�rna
	10.0f, 0.0f,  0.0f, 8.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 8.0f,  0.0f, 8.0f,

	// �ciana dolna
	10.0f, 0.0f,  0.0f, 8.0f,  0.0f, 0.0f,
	10.0f, 0.0f,  10.0f, 8.0f,  0.0f, 8.0f,
};

float floorVertices[] = {
	// �ciana przednia (x, y, z) - ok

		5.0f, 1.0f, 4.0f, 1.0f,   // F
		-5.0f, 1.0f, 4.0f, 1.0f,  // E
		-5.0f, 0.0f, 4.0f, 1.0f,  // A





	5.0f, 1.0f, 4.0f, 1.0f,   // F
	5.0f, 0.0f, 4.0f, 1.0f,   // B
	-5.0f, 0.0f, 4.0f, 1.0f,  // A



	// �ciana tylna -ok
	-5.0f, 1.0f, -4.0f, 1.0f, // H
		5.0f, 1.0f, -4.0f, 1.0f,  // G
			5.0f, 0.0f, -4.0f, 1.0f,  // D

	-5.0f, 0.0f, -4.0f, 1.0f, // C
	-5.0f, 1.0f, -4.0f, 1.0f, // H
	5.0f, 0.0f, -4.0f, 1.0f,  // D

	// �ciana lewa - ok
	-5.0f, 1.0f, -4.0f, 1.0f, // H
	-5.0f, 0.0f, 4.0f, 1.0f,  // A
	-5.0f, 1.0f, 4.0f, 1.0f,  // E


	-5.0f, 1.0f, -4.0f, 1.0f, // H
	-5.0f, 0.0f, -4.0f, 1.0f, // C
	-5.0f, 0.0f, 4.0f, 1.0f,  // A




	// �ciana prawa - o
	5.0f, 1.0f, -4.0f, 1.0f,  // G
	5.0f, 0.0f, 4.0f, 1.0f,   // B
	5.0f, 1.0f, 4.0f, 1.0f,   // F


	5.0f, 1.0f, -4.0f, 1.0f,  // G
	5.0f, 0.0f, -4.0f, 1.0f,  // D
	5.0f, 0.0f, 4.0f, 1.0f,   // B


	// �ciana g�rna -ok
	-5.0f, 1.0f, 4.0f, 1.0f,  // E
	5.0f, 1.0f, -4.0f, 1.0f,  // G
	5.0f, 1.0f, 4.0f, 1.0f,   // F


	-5.0f, 1.0f, 4.0f, 1.0f,  // E
	-5.0f, 1.0f, -4.0f, 1.0f, // H
	5.0f, 1.0f, -4.0f, 1.0f,  // G

	// �ciana dolna - ok

	-5.0f, 0.0f, 4.0f, 1.0f,  // A
	5.0f, 0.0f, -4.0f, 1.0f,  // D
	5.0f, 0.0f, 4.0f, 1.0f,   // B

	-5.0f, 0.0f, 4.0f, 1.0f,  // A
	-5.0f, 0.0f, -4.0f, 1.0f, // C
	5.0f, 0.0f, -4.0f, 1.0f,  // D
};




float floorNormals[] = {
    // Normals for �ciana przednia
    0.0f, 0.0f, -1.0f,  // F
    0.0f, 0.0f, -1.0f,  // E
    0.0f, 0.0f, -1.0f,  // A

    0.0f, -1.0f, 0.0f,  // F
    0.0f, -1.0f, 0.0f,  // B
    0.0f, -1.0f, 0.0f,  // A

    // Normals for �ciana tylna
    0.0f, 0.0f, 1.0f,  // H
    0.0f, 0.0f, 1.0f,  // G
    0.0f, 0.0f, 1.0f,  // D

    0.0f, 1.0f, 0.0f,  // C
    0.0f, 1.0f, 0.0f,  // H
    0.0f, 1.0f, 0.0f,  // D

    // Normals for �ciana lewa
    1.0f, 0.0f, 0.0f,  // H
    1.0f, 0.0f, 0.0f,  // A
    1.0f, 0.0f, 0.0f,  // E

    0.0f, 1.0f, 0.0f,  // H
    0.0f, 1.0f, 0.0f,  // C
    0.0f, 1.0f, 0.0f,  // A

    // Normals for �ciana prawa
    -1.0f, 0.0f, 0.0f,  // G
    -1.0f, 0.0f, 0.0f,  // B
    -1.0f, 0.0f, 0.0f,  // F

    0.0f, -1.0f, 0.0f,  // G
    0.0f, -1.0f, 0.0f,  // D
    0.0f, -1.0f, 0.0f,  // B

    // Normals for �ciana g�rna
    1.0f, 0.0f, 0.0f,  // E
    1.0f, 0.0f, 0.0f,  // G
    1.0f, 0.0f, 0.0f,  // F

    0.0f, -1.0f, 0.0f,  // E
    0.0f, -1.0f, 0.0f,  // H
    0.0f, -1.0f, 0.0f,  // G

    // Normals for �ciana dolna
    0.0f, -1.0f, 0.0f,  // A
    0.0f, -1.0f, 0.0f,  // D
    0.0f, -1.0f, 0.0f,  // B

    0.0f, 1.0f, 0.0f,  // A
    0.0f, 1.0f, 0.0f,  // C
    0.0f, 1.0f, 0.0f,  // D
};

#endif // FLOOR_H_INCLUDED

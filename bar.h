#pragma once
// Define bar geometry



#ifndef BAR_H_INCLUDED
#define BAR_H_INCLUDED
float barVertices[] = {
	// Positions          // Texture Coords
	-10.0f, 1.0f, -1.0f,  0.0f, 0.0f,
	 10.0f, 1.0f, -1.0f,  1.0f, 0.0f,
	 10.0f, 1.5f, -1.0f,  1.0f, 1.0f,
	-10.0f, 1.5f, -1.0f,  0.0f, 1.0f,

	-10.0f, 1.0f,  1.0f,  0.0f, 0.0f,
	 10.0f, 1.0f,  1.0f,  1.0f, 0.0f,
	 10.0f, 1.5f,  1.0f,  1.0f, 1.0f,
	-10.0f, 1.5f,  1.0f,  0.0f, 1.0f
};

int barIndices[] = {
	0, 1, 2, 2, 3, 0,  // Front face
	4, 5, 6, 6, 7, 4,  // Back face
	0, 1, 5, 5, 4, 0,  // Bottom face
	2, 3, 7, 7, 6, 2,  // Top face
	0, 3, 7, 7, 4, 0,  // Left face
	1, 2, 6, 6, 5, 1   // Right face
};

float barNormals[] = {
    // Front face
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    // Back face
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    // Bottom face
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    // Top face
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    // Left face
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    // Right face
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};

#endif // BAR_H_INCLUDED
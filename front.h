#pragma once
#ifndef FRONT_H_INCLUDED
#define FRONT_H_INCLUDED

int frontVertexCount = 3;

float frontVertices[] = {
    -1.0f, 1.0f,-1.0f,1.0f, //A
    -1.0f,-1.0f,-1.0f,1.0f, //B
    1.0f,-1.0f,-1.0f,1.0f, //C



};

float frontTexCoords[] = {
    // Dolna podstawa
    0.0f, 0.0f,  // A
    1.0f, 0.0f,  // B
    0.5f, 1.0f,  // C


};

float frontNormals[] = {
    // Dolna podstawa
    0.0f, 0.0f, -1.0f,  // A
    0.0f, 0.0f, 1.0f,   // B
    0.0f, 1.0f, 0.0f,   // C

    // Górna podstawa
    1.0f, 0.0f, -1.0f,  // D
    1.0f, 0.0f, 1.0f,   // E
    1.0f, 1.0f, 0.0f,   // F
};

#endif

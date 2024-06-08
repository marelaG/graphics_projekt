#pragma once

#ifndef ROOF_H_INCLUDED
#define ROOF_H_INCLUDED

int roofVertexCount = 18;

float roofVertices[] = {
    // Side walls
    0.0f, 0.0f, -1.0f, 1.0f,  // A
    0.0f, 1.0f, 0.0f, 1.0f,   // C
    2.0f, 1.0f, 0.0f, 1.0f,   // F

    0.0f, 0.0f, -1.0f, 1.0f,  // A
    2.0f, 1.0f, 0.0f, 1.0f,   // F
    2.0f, 0.0f, -1.0f, 1.0f,  // D

    0.0f, 0.0f, 1.0f, 1.0f,   // B
    0.0f, 1.0f, 0.0f, 1.0f,   // C
    2.0f, 1.0f, 0.0f, 1.0f,   // F

    0.0f, 0.0f, 1.0f, 1.0f,   // B
    2.0f, 1.0f, 0.0f, 1.0f,   // F
    2.0f, 0.0f, 1.0f, 1.0f,   // E

    0.0f, 0.0f, -1.0f, 1.0f,  // A
    0.0f, 0.0f, 1.0f, 1.0f,   // B
    2.0f, 0.0f, 1.0f, 1.0f,   // E

    0.0f, 0.0f, -1.0f, 1.0f,  // A
    2.0f, 0.0f, 1.0f, 1.0f,   // E
    2.0f, 0.0f, -1.0f, 1.0f,  // D
};

// Texture coordinates
float roofTexCoords[] = {
    // Side walls
    0.0f, 0.0f,  // A
    1.0f, 0.0f,  // C
    1.0f, 1.0f,  // F

    0.0f, 0.0f,  // A
    1.0f, 1.0f,  // F
    0.0f, 1.0f,  // D

    0.0f, 0.0f,  // B
    1.0f, 0.0f,  // C
    1.0f, 1.0f,  // F

    0.0f, 0.0f,  // B
    1.0f, 1.0f,  // F
    0.0f, 1.0f,  // E

    0.0f, 0.0f,  // A
    1.0f, 0.0f,  // B
    1.0f, 1.0f,  // E

    0.0f, 0.0f,  // A
    1.0f, 1.0f,  // E
    0.0f, 1.0f,  // D
};

// Normals
float roofNormals[] = {
    // Side walls
    0.0f, 0.7071f, 0.7071f,  // Normal for triangle ACF
    0.0f, 0.7071f, 0.7071f,  // Normal for triangle ACF
    0.0f, 0.7071f, 0.7071f,  // Normal for triangle ACF

    0.0f, 0.7071f, 0.7071f,  // Normal for triangle AFD
    0.0f, 0.7071f, 0.7071f,  // Normal for triangle AFD
    0.0f, 0.7071f, 0.7071f,  // Normal for triangle AFD

    0.0f, 0.7071f, -0.7071f,  // Normal for triangle BCF
    0.0f, 0.7071f, -0.7071f,  // Normal for triangle BCF
    0.0f, 0.7071f, -0.7071f,  // Normal for triangle BCF

    0.0f, 0.7071f, -0.7071f,  // Normal for triangle BFE
    0.0f, 0.7071f, -0.7071f,  // Normal for triangle BFE
    0.0f, 0.7071f, -0.7071f,  // Normal for triangle BFE

    0.0f, -1.0f, 0.0f,  // Normal for triangle ABE
    0.0f, -1.0f, 0.0f,  // Normal for triangle ABE
    0.0f, -1.0f, 0.0f,  // Normal for triangle ABE

    0.0f, -1.0f, 0.0f,  // Normal for triangle AED
    0.0f, -1.0f, 0.0f,  // Normal for triangle AED
    0.0f, -1.0f, 0.0f,  // Normal for triangle AED
};

#endif // ROOF_H_INCLUDED

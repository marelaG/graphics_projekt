#pragma once

#ifndef ROOF_H_INCLUDED
#define ROOF_H_INCLUDED

int roofVertexCount = 24;

float roofVertices[] = {
    // Dolna podstawa 

      1.0f, 0.0f, 0.0f, 1.0f,  // C 
         0.0f, 0.0f, -1.0f, 1.0f, // B 
        0.0f, 0.0f, 1.0f, 1.0f,  // A




        // Górna podstawa 
            0.0f, 2.0f, -1.0f, 1.0f, // E 
         1.0f, 2.0f, 0.0f, 1.0f,  // F

         0.0f, 2.0f, 1.0f, 1.0f,  // D 


         // Ściany boczne (rotated around Y-axis)
         0.0f, 0.0f, 1.0f, 1.0f,  // A -> (Z, Y, -X)
         1.0f, 0.0f, 0.0f, 1.0f,  // C -> (Z, Y, -X)
         1.0f, 2.0f, 0.0f, 1.0f,  // F -> (Z, Y, -X)

         0.0f, 0.0f, 1.0f, 1.0f,  // A -> (Z, Y, -X)
         1.0f, 2.0f, 0.0f, 1.0f,  // F -> (Z, Y, -X)
         0.0f, 2.0f, 1.0f, 1.0f,  // D -> (Z, Y, -X)

         0.0f, 0.0f, -1.0f, 1.0f, // B -> (Z, Y, -X)
         1.0f, 0.0f, 0.0f, 1.0f,  // C -> (Z, Y, -X)
         1.0f, 2.0f, 0.0f, 1.0f,  // F -> (Z, Y, -X)

         0.0f, 0.0f, -1.0f, 1.0f, // B -> (Z, Y, -X)
         1.0f, 2.0f, 0.0f, 1.0f,  // F -> (Z, Y, -X)
         0.0f, 2.0f, -1.0f, 1.0f, // E -> (Z, Y, -X)

         0.0f, 0.0f, 1.0f, 1.0f,  // A -> (Z, Y, -X)
         0.0f, 0.0f, -1.0f, 1.0f, // B -> (Z, Y, -X)
         0.0f, 2.0f, -1.0f, 1.0f, // E -> (Z, Y, -X)

         0.0f, 0.0f, 1.0f, 1.0f,  // A -> (Z, Y, -X)
         0.0f, 2.0f, -1.0f, 1.0f, // E -> (Z, Y, -X)
         0.0f, 2.0f, 1.0f, 1.0f,  // D -> (Z, Y, -X)
};

// Normals for each vertex
float roofNormals[] = {
    // Bottom base (facing -Z, becomes -X after rotation)
        // Górna podstawa



    0.7071f, 0.0f, -0.7071f, 0.0f, // B
    0.0f, 0.0f, -1.0f,  0.0f,      // F
        0.7071f, 0.0f, -0.7071f, 0.0f, // C


    -0.7071f, 0.0f, -0.7071f,0.0f, // A
    0.0f, 0.0f, -1.0f,      0.0f,  // B
    0.0f, 0.0f, -1.0f,   0.0f,    // C





    // Ściany boczne


    0.7071f, 0.0f, -0.7071f, 0.0f, // B
    0.7071f, 0.0f, -0.7071f, 0.0f, // C
    0.0f, 0.0f, -1.0f,  0.0f,      // F

     0.7071f, 0.0f, -0.7071f, 0.0f, // B
    0.0f, 0.0f, -1.0f,    0.0f,    // F
    0.0f, 0.0f, -1.0f,   0.0f,     // E

    -0.7071f, 0.0f, -0.7071f,0.0f, // A
    0.0f, 0.0f, -1.0f,      0.0f,  // B
    0.0f, 0.0f, -1.0f,   0.0f,    // C

    -0.7071f, 0.0f, -0.7071f,0.0f, // A
    0.0f, 0.0f, -1.0f,   0.0f,     // C
    0.0f, 0.0f, -1.0f,   0.0f,     // F

    -0.7071f, 0.0f, -0.7071f,0.0f, // A
    0.0f, 0.0f, -1.0f,      0.0f,  // B
    0.0f, 0.0f, -1.0f,   0.0f,    // C

    -0.7071f, 0.0f, -0.7071f,0.0f, // A
    0.0f, 0.0f, -1.0f,   0.0f,     // C
    0.0f, 0.0f, -1.0f,   0.0f,     // F




};

// Współrzędne tekstur
float roofTexCoords[] = {
    // Dolna podstawa
    0.0f, 0.0f,  // A
    1.0f, 0.0f,  // B
    0.5f, 1.0f,  // C

    // Górna podstawa
    0.0f, 0.0f,  // D
    1.0f, 0.0f,  // E
    0.5f, 1.0f,  // F

    // Ściany boczne
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

#endif // ROOF_H_INCLUDED
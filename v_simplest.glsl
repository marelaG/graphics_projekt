#version 330

// Uniform variables
uniform mat4 P;             // Projection matrix
uniform mat4 V;             // View matrix
uniform mat4 M;             // Model matrix
uniform vec4 lp1 = vec4 (-5.0f, 8.0f, -4.0f, 1.0f);
uniform vec4 lp2 = vec4 (5.0f, 8.0f, 4.0f, 1.0f); //orange


// Uniforms
uniform vec4 lightColor2 = vec4(1.0f, 0.5f, 0.0f, 1.0f); // Light color 1 (blue)
uniform vec4 lightColor1 = vec4(1.0f, 1.0f, 0.0f, 1.0f); // Light color 2 (yellow)



// Vertex attributes
in vec4 vertex;             // Vertex position in model space
in vec4 color;              // Vertex color
in vec4 normal;             // Vertex normal in model space
in vec2 texCoord;           // Vertex texture coordinates

// Interpolated variables to be passed to the fragment shader
out vec4 ic;                // Interpolated color
out vec4 l1;                // Light direction vector 1 in eye space
out vec4 l2;                // Light direction vector 2 in eye space
out vec4 n;                 // Normal vector in eye space
out vec4 v;                 // View vector in eye space
out vec2 iTexCoord0;        // Interpolated texture coordinates

void main(void) {
    // Transform the vertex position to eye space
    vec4 vertexEyeSpace = V * M * vertex;

    // Calculate the light direction vectors in eye space
    vec4 lightPositionEyeSpace1 = V * lp1;
    vec4 lightPositionEyeSpace2 = V * lp2;
    l1 = normalize(lightPositionEyeSpace1 - vertexEyeSpace);
    l2 = normalize(lightPositionEyeSpace2 - vertexEyeSpace);
    
    // Calculate the view vector in eye space
    v = normalize(-vertexEyeSpace);
    
    // Transform the normal to eye space and normalize it
    n = normalize(V * M * normal);
    
    // Pass the texture coordinates to the fragment shader
    iTexCoord0 = texCoord;
    
    // Pass the vertex color to the fragment shader
    ic = color;
    
    // Calculate the final position of the vertex in clip space
    gl_Position = P * vertexEyeSpace;
}

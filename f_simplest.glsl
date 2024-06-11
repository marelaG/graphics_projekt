#version 330

// Uniforms
uniform sampler2D textureMap0; // The texture map
uniform vec4 lightColor2 = vec4(1.0f, 0.5f, 0.0f, 1.0f); // Light color 1 (blue)
uniform vec4 lightColor1 = vec4(1.0f, 1.0f, 0.0f, 1.0f); // Light color 2 (yellow)

// Output
out vec4 pixelColor; // Final pixel color

// Interpolated inputs from the vertex shader
in vec2 iTexCoord0; // Interpolated texture coordinates
in vec4 ic;         // Interpolated vertex color
in vec4 l1;         // Light direction vector 1 in eye space
in vec4 l2;         // Light direction vector 2 in eye space
in vec4 n;          // Normal vector in eye space
in vec4 v;          // View direction vector in eye space

void main(void) {
    // Normalize interpolated vectors
    vec3 ml1 = normalize(l1.xyz); // Light direction 1
    vec3 ml2 = normalize(l2.xyz); // Light direction 2
    vec3 mn = normalize(n.xyz);   // Normal direction
    vec3 mv = normalize(v.xyz);   // View direction
    vec3 mr1 = reflect(-ml1, mn); // Reflected light direction 1
    vec3 mr2 = reflect(-ml2, mn); // Reflected light direction 2

    // Surface parameters
    vec4 kd = texture(textureMap0, iTexCoord0); // Texture color (diffuse color)
    vec4 ks = vec4(1.0, 1.0, 1.0, 1.0); // Specular color (white)

    // Phong lighting model for light 1
    float nl1 = max(dot(mn, ml1), 0.0); // Diffuse term for light 1
    float rv1 = pow(max(dot(mr1, mv), 0.0), 50.0); // Specular term for light 1

    // Phong lighting model for light 2
    float nl2 = max(dot(mn, ml2), 0.0); // Diffuse term for light 2
    float rv2 = pow(max(dot(mr2, mv), 0.0), 50.0); // Specular term for light 2

    // Separate ambient terms for each light
    vec4 ambient1 = 0.1 * kd * lightColor1; // Ambient term for light 1
    vec4 ambient2 = 0.1 * kd * lightColor2; // Ambient term for light 2

    // Combining the lighting components for both lights
    vec4 diffuse1 = nl1 * kd * lightColor1; // Diffuse term for light 1
    vec4 diffuse2 = nl2 * kd * lightColor2; // Diffuse term for light 2
    vec4 specular1 = rv1 * ks * lightColor1; // Specular term for light 1
    vec4 specular2 = rv2 * ks * lightColor2; // Specular term for light 2

    // Final pixel color by combining all lighting components
    pixelColor = ambient1 + ambient2 + diffuse1 + diffuse2 + specular1 + specular2;
}

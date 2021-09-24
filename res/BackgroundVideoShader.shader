#shader vertex
#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
out vec2 UV;
void main() {

    // Output position of the vertex, in clip space : MVP * position
    gl_Position = vec4(vertexPosition, 1);

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}
#shader fragment
#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main() {

    // Output color = color of the texture at the specified UV
    color = texture(myTextureSampler, UV).rgb;
}

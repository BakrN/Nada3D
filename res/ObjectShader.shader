#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 i_Color;
layout(location = 2) in vec2 vexterUV;
out vec3 fragmentColor;


uniform mat4 MVP;
void main() {
	gl_Position = MVP * vec4(position, 1.0f);
	fragmentColor = i_Color;
}
;

#shader fragment
#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;

// Ouput data
out vec4 color;

void main() {

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	// could add texture; 
	color = vec4(0.5f, 1.0f, 0.0f, 1.0f);

};
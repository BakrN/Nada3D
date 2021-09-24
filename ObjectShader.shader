#shader vertex
#version 330 core
layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec4 v_Color;
layout(location = 3) in vec2 v_TexUV;
layout(location = 4) in float v_TexSlot;

out	vec3 f_Normal;
out vec4 f_Color;
out vec2 f_TexUV;
out float f_TexSlot;
uniform mat4 v_ViewProjection;
uniform mat4 v_Transform;

void main() {
	gl_Position = v_ViewProjection * vec4(v_Position, 1.0f)  /* *vec4(1.0f,1.0f,-1.0f,1.0f)*/;
	f_Normal = v_Normal;
	f_Color = v_Color;
	f_TexUV = v_TexUV;
	f_TexSlot = v_TexSlot;
}
;

#shader fragment
#version 330 core
in float f_TexSlot;
in vec2 f_TexUV;
in vec4 f_Color; 
out vec4 color;
uniform sampler2D TextureSlot[32]; 
void main() {
	int i = int(f_TexSlot); 
	color = texture(TextureSlot[i], f_TexUV) * f_Color;

};
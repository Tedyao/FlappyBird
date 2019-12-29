#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoor;

out vec2 texCoors;
uniform mat4 trans_matrix;
uniform mat4 rot_matrix;
uniform mat4 orth_matrix;

void main() {
	gl_Position = orth_matrix * trans_matrix * rot_matrix * position;
	texCoors = textCoor;
}



#shader fragment
#version 330 core
in vec2 texCoors;
out vec4 color;
uniform sampler2D u_Texture;
uniform vec2 offset;

void main() {
	vec2 myTc = vec2(texCoors.x / 5 + offset.x / 5, texCoors.y / 5 + offset.y / 5);
	color = texture(u_Texture, myTc);

}

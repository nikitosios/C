#version 330

layout(location = 0) in vec3 position;

uniform mat4 MVP;

out vec3 color;

void main() {
	color = vec3(1.0, 0.0, 0.0);
	gl_Position = MVP * vec4(position, 1.0);
}

#version 330

layout(location = 0) in vec3 position;

out vec3 color;

void main() {
	color = vec3(1.0, 0.0, 0.0);
	gl_Position = vec4(position, 1.0);
}

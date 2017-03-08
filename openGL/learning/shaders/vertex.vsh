#version 330

in vec3 position;
in vec3 color;

uniform mat4 MVP;

out vec3 FragColor;

void main()
{
	FragColor = color;
	gl_Position = MVP * vec4(position, 1.0);
}

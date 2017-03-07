#version 330

in vec3 position;

uniform mat4 MVP;

out vec3 FragColor;

void main()
{
	FragColor = vec3(1.0, 0.0, 0.0);
	gl_Position = MVP * vec4(position, 1.0);
}

#version 330

in vec2 UV;

uniform sampler2D myTextureSampler;

out vec3 color;

void main(){
	color = texture(myTextureSampler, UV).rgb;
}

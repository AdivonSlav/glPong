R"(
#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;

out vec4 v_Colour;

uniform mat4 projMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 modelMatrix;

void main()
{
	gl_Position = projMatrix * modelMatrix * vec4(position, 1.0f);
	v_Colour = colour;
}
)"

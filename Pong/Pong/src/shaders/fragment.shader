R"(
#version 440 core

out vec4 f_Colour;

uniform vec4 objectColour;

void main()
{
	f_Colour = objectColour;
}
)"

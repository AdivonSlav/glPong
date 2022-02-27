R"(
#version 440 core

out vec4 f_Colour;

in vec4 v_Colour;

void main()
{
	f_Colour = v_Colour;
}
)"

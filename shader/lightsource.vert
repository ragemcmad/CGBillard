#version 330
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable
// default330.vert: a simple vertex shader
//
// notes:
// GL_ARB_explicit_uniform_location is not needed for version >= 430
// GL_ARB_separate_shader_objects is not needed for version >= 410
uniform mat4 matrix;
uniform mat4 projmatrix;
uniform mat4 viewmatrix;
in vec4 vert;
// #version 330: in, location=3

void main()
{
    gl_Position = (((projmatrix * viewmatrix) * matrix) * vert);

}

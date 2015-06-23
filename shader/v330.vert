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
layout(location = 0) out vec4 texC;
layout(location = 1) out vec4 normalvector;
layout(location = 2) out vec4 vertex;
in vec4 normal;
in vec4 vert;
in vec4 texCoord;
// #version 330: in, location=3

void main()
{
    vertex = matrix * vert;
    normalvector = transpose(inverse(matrix))* normal;
    texC = texCoord;
    gl_Position =  (((projmatrix * viewmatrix) * matrix) * vert);

}

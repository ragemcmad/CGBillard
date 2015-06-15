#version 330
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable
out vec4 texC;
in vec4 vert;
in vec4 texCoord;
uniform mat4 matrix;
// #version 330: in, location=3

void main()
{
    texC = texCoord;
    gl_Position =matrix*vert;
}

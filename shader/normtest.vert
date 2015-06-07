#version 130
// default130.vert: a simple vertex shader
uniform mat4 matrix;
uniform mat4 projmatrix;
uniform mat4 viewmatrix;
attribute vec4 vert;
attribute vec4 normCoord;
varying vec4 normC;
void main()
{
    //col = color;
    //col = vec4(1,1,1,1);
    normC = normCoord;
    gl_Position =  (((projmatrix * viewmatrix) * matrix) * vert);
  //  gl_Position = vert * vec4(0.5, 0.5, 1, 1);
}


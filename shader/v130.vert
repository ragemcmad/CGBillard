#version 130
// default130.vert: a simple vertex shader
uniform mat4 matrix;
uniform mat4 projmatrix;
uniform mat4 viewmatrix;
attribute vec4 normal;
attribute vec4 vert;
//attribute vec4 color;
//varying vec4 col;
attribute vec4 texCoord; // #version 330: in, location=3
varying vec4 texC; // #version 330: out
varying vec4 normalvector;
void main()
{
    //col = color;
    //col = vec4(1,1,1,1);
    normalvector =  normal;
    texC = texCoord;
    gl_Position =  (((projmatrix * viewmatrix) * matrix) * vert);
  //  gl_Position = vert * vec4(0.5, 0.5, 1, 1);
}

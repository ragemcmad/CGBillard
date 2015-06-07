#version 130
// default130.frag: a simple fragment shader
//varying vec4 col;
varying vec4 normC; // #version 330: in
void main()
{
//gl_FragColor = col;
//gl_FragColor = vec4(1,1,1,1);
    gl_FragColor = normC;
}

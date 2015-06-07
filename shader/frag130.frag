#version 130
// default130.frag: a simple fragment shader
//varying vec4 col;
varying vec4 texC; // #version 330: in
varying vec4 normalvector;
uniform sampler2D texture;

void main()
{
    //gl_FragColor = texture2D(texture, vec2(texC.x, texC.y));
    gl_FragColor = normalvector;
}

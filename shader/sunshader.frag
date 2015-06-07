#version 330
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable
// default330.frag: a simple fragment shader
//
// notes:
// GL_ARB_separate_shader_objects is not needed for version >= 410

out vec4 fragColor;
in vec4 texC;
uniform float timer;
uniform sampler2D texture;
uniform sampler2D textureWave;

// must be at 0
void main()
{
    float time = mod(timer,5000);
    time /= 5000;

    vec4 offset = texture2D(textureWave, vec2(texC.x+time,texC.y+time));
    offset *= 0.005;
    fragColor = texture2D(texture, vec2(texC.x+offset.r,texC.y+offset.g));
    //fragColor = vec4(time,0,0,1);//texture2D(textureWave, vec2(texC.x,texC.y));

}

#version 330
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable

out vec4 fragColor;
in vec4 texC;
uniform sampler2D texture;

// must be at 0
void main()
{
    fragColor = texture2D(texture, vec2(texC.x, texC.y));
    if(fragColor.r > 0.98 && fragColor.g < 0.02 && fragColor.b > 0.98)
    {
        fragColor.a = 0;
    }


}

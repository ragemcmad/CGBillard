#version 330
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable
// default330.frag: a simple fragment shader
//
// notes:
// GL_ARB_separate_shader_objects is not needed for version >= 410

out vec4 fragColor;
in vec4 texC;
in vec4 normalvector;
in vec4 vertex;
uniform sampler2D texture;

// must be at 0
void main()
{
    vec3 vert = -normalize(vertex).xyz;
    vec3 normal = normalize(normalvector).xyz;
    float angle = dot(vert, normal);
    if(angle <0)
        angle = 0;
    vec4 color =  texture2D(texture, vec2(texC.x, texC.y));
    color.r = color.r * angle;
    color.g = color.g * angle;
    color.b = color.b * angle;

    color = vec4(color.rgb,1)*4;
    fragColor = vec4(0.05,0.05,0.05,1)*texture2D(texture, vec2(texC.x, texC.y)) + color;

}

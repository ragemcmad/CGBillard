#version 330
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable
// default330.frag: a simple fragment shader
//
// notes:
// GL_ARB_separate_shader_objects is not needed for version >= 410

out vec4 fragColor;
uniform vec3 lightintensity;

// must be at 0
void main()
{
    //ambient
    vec3 lights = normalize(lightintensity)*3;
    fragColor = vec4(lights,1);
}

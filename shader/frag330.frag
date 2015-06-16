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
uniform vec3 lightpositions[4];
uniform vec3 lightintensity[4];
uniform vec4 cameraposition;

// must be at 0
void main()
{
    //ambient
    fragColor = vec4(0.05,0.05,0.05,1)*texture2D(texture, vec2(texC.x, texC.y));

    for(int i = 0;i<4;i++)
    {
        vec3 vert = -normalize(vertex.xyz-lightpositions[i]);//-lightpositions[i]);
        vec3 normal = normalize(normalvector.xyz);
        float angle = dot(vert, normal);
        if(angle <0)
            angle = 0;
        vec4 color =  texture2D(texture, vec2(texC.x, texC.y));
        color.r = color.r * angle *lightintensity[i].r*(1.0/distance(vertex.xyz,lightpositions[i]));
        color.g = color.g * angle *lightintensity[i].g*(1.0/distance(vertex.xyz,lightpositions[i]));
        color.b = color.b * angle *lightintensity[i].b*(1.0/distance(vertex.xyz,lightpositions[i]));

        //color = vec4(color.rgb,1);
        fragColor = fragColor + color;

    }


}

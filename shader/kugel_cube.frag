#version 330
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_uniform_location : enable
// default330.frag: a simple fragment shader
//
// notes:
// GL_ARB_separate_shader_objects is not needed for version >= 410

layout(location = 0) in vec4 texC;
layout(location = 1) in vec4 normalvector;
layout(location = 2) in vec4 vertex;
out vec4 fragColor;
uniform sampler2D colortex;
uniform vec3 lightpositions[4];
uniform vec3 lightintensity[4];
uniform vec3 cameraposition;

uniform samplerCube cubeMap;
uniform vec3 kugelPos;

// must be at 0
void main()
{
    vec4 fragTex = texture(colortex, vec2(texC.x, texC.y));
    //ambient
    fragColor = vec4(0.05,0.05,0.05,1)*fragTex;
    float alpha = fragColor.a;
    vec4 colorSpecAll=vec4(0,0,0,0);

    vec3 normal = normalize(normalvector.xyz);

    for(int i = 0;i<4;i++)
    {
        float anglespec = 0;

        vec3 vert = -normalize(vertex.xyz-lightpositions[i]);//-lightpositions[i]);
        float angle = dot(vert, normal);

        vec3 cPos = normalize(cameraposition);
        vec3 rayA = normalize(reflect(-vert,normal));
        vec3 rayB = normalize(cPos+vert);
        anglespec = pow(dot(rayA,rayB),8);


        angle = max(angle, 0);
        vec4 color =  fragTex;
        color.r = color.r * angle *lightintensity[i].r*(1.0/distance(vertex.xyz,lightpositions[i]));
        color.g = color.g * angle *lightintensity[i].g*(1.0/distance(vertex.xyz,lightpositions[i]));
        color.b = color.b * angle *lightintensity[i].b*(1.0/distance(vertex.xyz,lightpositions[i]));


        anglespec = clamp(anglespec, 0, 3.1415926/4);
        vec4 colorspec = fragTex;
        colorspec.r = max(colorspec.r * anglespec,0);
        colorspec.g = max(colorspec.g * anglespec,0);
        colorspec.b = max(colorspec.b * anglespec,0);

        colorSpecAll = colorSpecAll + colorspec;
        //color = vec4(color.rgb,1);
        fragColor = fragColor + color;

    }
    fragColor.a = 1;

    //fragColor.a= 0.3;
//    max(fragColor.a,0.4);

    fragColor.rgb += colorSpecAll.rgb;


    vec3 incidentVecWS = normalize(vertex.xyz - cameraposition.xyz);
    vec3 reflectedVecWS = reflect(incidentVecWS, normal);
    vec3 refractedVecWS = refract(incidentVecWS, normal, 1.5);

    vec4 reflectedColor = texture(cubeMap, reflectedVecWS);
    vec4 refractedColor = texture(cubeMap, refractedVecWS);
    vec3 localPos = normalize(vertex.xyz - kugelPos);
//    vec4 reflectedColor = texture(cubeMap, localPos);

    fragColor.rgb = mix(fragColor.rgb, reflectedColor.rgb, 0.7);
//    fragColor.rgb = mix(fragColor.rgb, refractedColor.rgb, 0.7);

//    fragColor.rgb = localPos * 2 - vec3(1,1,1);

    //fragColor.a = 1;
}

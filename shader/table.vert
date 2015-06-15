#version 330
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable
// default330.vert: a simple vertex shader
//
// notes:
// GL_ARB_explicit_uniform_location is not needed for version >= 430
// GL_ARB_separate_shader_objects is not needed for version >= 410
uniform mat4 matrix;
uniform mat4 projmatrix;
uniform mat4 viewmatrix;
out vec4 texC;
out vec4 normalvector;
out vec4 vertex;
in vec4 normal;
in vec4 vert;
in vec4 texCoord;
uniform float WaveActive[16];
uniform float WaveTime[16];
uniform float WavePosX[16];
uniform float WavePosZ[16];

// #version 330: in, location=3

void main()
{
    vec4 vertexWave = vec4(0,0,0,0);
    vec4 normalWave = normal;
    for(int i = 0;i< 16;i++)
    {
        if(WaveActive[i] == 1)
        {
            float deltaX = vert.x-WavePosX[i];
            float deltaZ = vert.z-WavePosZ[i];

            float distanz = sqrt(deltaX*deltaX+deltaZ*deltaZ);
            if(distanz>WaveTime[i]-3.1415926 && distanz < WaveTime[i])
            {
                vec2 normalDirection = vec2(deltaX,deltaZ);
                normalDirection = normalize(normalDirection);
                vertexWave.y = vertexWave.y + ((-cos((WaveTime[i]-distanz)*2.0)*1.0+1.0)*(1.0-(WaveTime[i]/40.0)));
                normalWave.x = normalWave.x+normalDirection.x *sin((WaveTime[i]-distanz)*2)*(vertexWave.y);
                normalWave.z = normalWave.z+normalDirection.y *sin((WaveTime[i]-distanz)*2)*(vertexWave.y);
            }
        }
    }
    vertex = matrix * (vertexWave + vert);
    normalvector = transpose(inverse(matrix))* normalWave;
    texC = texCoord;
    gl_Position =  (((projmatrix * viewmatrix) * matrix) * (vertexWave+vert));

}

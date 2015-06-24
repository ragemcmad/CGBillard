#version 330
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable
// default330.vert: a simple vertex shader
//
// notes:
// GL_ARB_explicit_uniform_location is not needed for version >= 430
// GL_ARB_separate_shader_objects is not needed for version >= 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

layout(location = 0) in vec4 texC[];
layout(location = 1) in vec4 normalvector[];
layout(location = 2) in vec4 vertex[];

layout(location = 0) out vec4 fragTexC;
layout(location = 1) out vec4 fragNormalvector;
layout(location = 2) out vec4 fragVertex;

uniform mat4 cubeViews[6];
uniform mat4 cubeProj;

void main()
{

  for (int i = 0; i < 6; ++i)
  {
    // cubemap layer
    gl_Layer = i;


    // dreieck
    for (int k = 0; k < 3; ++k)
    {
      // normalerweise im vertexshader
      gl_Position = cubeProj * (cubeViews[i] * vertex[k]);

      fragTexC = texC[k];
      fragNormalvector = normalvector[k];
      fragVertex = vertex[k];
      EmitVertex();
    }
    EndPrimitive();
  }

}

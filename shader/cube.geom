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

in vec4 texC[];
in vec4 normalvector[];
in vec4 vertex[];

out fragTexC;
out fragNormalvector;
out fragVertex;

uniform mat4 cubeViews[6];
uniform mat4 cubeProj;

void main()
{

  for (int i = 0; i < 6; ++i)
  {
    gl_Layer = i;


    for (int k = 0; k < 3; ++k)
    {
      gl_Position = cubeProj * (cubeViews[i] * vertex[k]);

      fragTexC = texC[k];
      fragNormalvector = normalvector[k];
      fragVertex = vertex[k];
      EmitVertex();
    }
    EndPrimitive();
  }

}

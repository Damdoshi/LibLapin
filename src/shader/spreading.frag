R"XXX(
/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Spreading
*/

varying vec2		vClip;
varying vec4		vColor;

uniform sampler2D	Layout;
uniform sampler2D	Previous;
uniform float		Random;
uniform float           Regular;

bool			rand(vec2 co)
{
  if (Regular > 0.5)
    return (false);
  if (mod(Random * co.x * co.y, 2.0) > 0.5)
    return (true);
  return (false);
}

void			main()
{
  vec3			LayoutEdge = texture2D(Layout, gl_TexCoord[0].xy).xyz;
  vec3			Black = vec3(0.0, 0.0, 0.0);

  vec4			Middle = texture2D(Previous, gl_TexCoord[0].xy);
  vec4			Top = texture2D(Previous, gl_TexCoord[1].xy);
  vec4			Bottom = texture2D(Previous, gl_TexCoord[2].xy);
  vec4			Left = texture2D(Previous, gl_TexCoord[3].xy);
  vec4			Right = texture2D(Previous, gl_TexCoord[4].xy);

  if (LayoutEdge == Black)
    {
      gl_FragColor = Middle;
      return ;
    }
  if (rand(gl_TexCoord[0].xy))
    {
      gl_FragColor = Middle;
      return ;
    }
  if (Top.xyz != Black)
    {
      gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
      return ;
    }
  if (Bottom.xyz != Black)
    {
      gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
      return ;
    }
  if (Left.xyz != Black)
    {
      gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
      return ;
    }
  if (Right.xyz != Black)
    {
      gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
      return ;
    }
  gl_FragColor = Middle;
}
)XXX"

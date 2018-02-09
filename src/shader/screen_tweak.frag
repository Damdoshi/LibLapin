R"XXX(
/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Screen Tweak shader
*/

uniform sampler2D	Picture;
uniform float		Blur;
uniform float		Luminosity;
uniform float		Red;
uniform float		Green;
uniform float		Blue;
uniform float		InvertColor;
uniform float		GrayScale;
uniform float		BlackNWhite;
uniform float		ColorBlind;

uniform float		NoiseType;
uniform float		NoiseColor;
uniform float		NoiseStrenght;
uniform float		Random;

float			rand(float a, float b, float c)
{
    return fract(sin(dot(vec2(b + 300.0, a + 300.0) * c * Random, vec2(12.9898,78.233))) * 43758.5453123);
}

void			main()
{
  vec3			swi;
  vec2			x = vec2(Blur, 0.0);
  vec2			y = vec2(0.0, Blur);
  vec3			noise;
  float     gray_final;
  int  			gray_count;
  float			avg;
  int       avg_i;

  vec4			Pixel =
    texture2D(Picture, gl_TexCoord[0].xy) * 4.0 +
    texture2D(Picture, gl_TexCoord[0].xy - x) * 2.0 +
    texture2D(Picture, gl_TexCoord[0].xy + x) * 2.0 +
    texture2D(Picture, gl_TexCoord[0].xy - y) * 2.0 +
    texture2D(Picture, gl_TexCoord[0].xy + y) * 2.0 +
    texture2D(Picture, gl_TexCoord[0].xy - x - y) * 1.0 +
    texture2D(Picture, gl_TexCoord[0].xy - x + y) * 1.0 +
    texture2D(Picture, gl_TexCoord[0].xy + x - y) * 1.0 +
    texture2D(Picture, gl_TexCoord[0].xy + x + y) * 1.0
    ;

  Pixel = gl_Color * (Pixel / 16.0);

  Pixel.x = clamp(Pixel.x * Red + (Luminosity - 1.0), 0.0, 1.0);
  Pixel.y = clamp(Pixel.y * Green + (Luminosity - 1.0), 0.0, 1.0);
  Pixel.z = clamp(Pixel.z * Blue + (Luminosity - 1.0), 0.0, 1.0);

  if (InvertColor > 0.5)
    {
      Pixel.x = 1.0 - Pixel.x;
      Pixel.y = 1.0 - Pixel.y;
      Pixel.z = 1.0 - Pixel.z;
    }
  if (ColorBlind < 0.5)
    swi.xyz = Pixel.xyz;
  else if (ColorBlind < 1.5)
    {
      swi.x = Pixel.x;
      swi.y = Pixel.z;
      swi.z = Pixel.y;
    }
  else if (ColorBlind < 2.5)
    {
      swi.x = Pixel.y;
      swi.y = Pixel.z;
      swi.z = Pixel.x;
    }
  else if (ColorBlind < 3.5)
    {
      swi.x = Pixel.z;
      swi.y = Pixel.y;
      swi.z = Pixel.x;
    }
  else
    {
      swi.x = Pixel.z;
      swi.y = Pixel.x;
      swi.z = Pixel.y;
    }
  Pixel.x = swi.x;
  Pixel.y = swi.y;
  Pixel.z = swi.z;

  if (GrayScale > 0.9)
    {
      avg_i = int(((Pixel.x + Pixel.y + Pixel.z) / 3.0) * 255.0);
      if (GrayScale > 254.5)
      {
         gray_final = float(avg_i) / 255.0;
      }
      else
      {
        gray_count = int(255.0 / GrayScale);
        gray_count = gray_count * (avg_i / gray_count);
        gray_final = float(gray_count) / 255.0;
      }
      Pixel.xyz = vec3(gray_final, gray_final, gray_final);
    }

  if (NoiseType > 0.5)
    {
      if (NoiseType < 1.5)
	{
	  noise = vec3
	    (rand(gl_TexCoord[0].x, gl_TexCoord[0].y, 2.0),
	     rand(gl_TexCoord[0].x, gl_TexCoord[0].y, 3.0),
	     rand(gl_TexCoord[0].x, gl_TexCoord[0].y, 4.0));
	}
      else if (NoiseType < 2.5)
	{
	  noise = vec3
	    (rand(1.0, gl_TexCoord[0].y, 2.0),
	     rand(1.0, gl_TexCoord[0].y, 3.0),
	     rand(1.0, gl_TexCoord[0].y, 4.0));
	}
      else if (NoiseType < 3.5)
	{
	  noise = vec3
	    (rand(gl_TexCoord[0].x, 1.0, 2.0),
	     rand(gl_TexCoord[0].x, 1.0, 3.0),
	     rand(gl_TexCoord[0].x, 1.0, 4.0));
	}

      if (NoiseColor < 0.5)
	{
	  Pixel.x += noise.x * NoiseStrenght;
	  Pixel.y += noise.y * NoiseStrenght;
	  Pixel.z += noise.z * NoiseStrenght;
	}
      else if (NoiseColor < 1.5)
	{
	  avg = (noise.x + noise.y + noise.z) / 3.0;
	  Pixel.x += avg * NoiseStrenght;
	  Pixel.y += avg * NoiseStrenght;
	  Pixel.z += avg * NoiseStrenght;
	}
      else if (NoiseColor < 2.5)
	{
	  avg = (noise.x + noise.y + noise.z) / 3.0;
	  if (avg < 0.5)
	    {
	      Pixel.x += -NoiseStrenght;
	      Pixel.y += -NoiseStrenght;
	      Pixel.z += -NoiseStrenght;
	    }
	  else
	    {
	      Pixel.x += NoiseStrenght;
	      Pixel.y += NoiseStrenght;
	      Pixel.z += NoiseStrenght;
	    }
	}
      Pixel.x = clamp(Pixel.x, 0.0, 1.0);
      Pixel.y = clamp(Pixel.y, 0.0, 1.0);
      Pixel.z = clamp(Pixel.z, 0.0, 1.0);
    }

  gl_FragColor = Pixel;
}
)XXX"

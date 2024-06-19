// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		<iostream>
#include		"lapin_private.h"

static t_bunny_shader	*gl_normal_map_shader = NULL;

// WindowSize
// ColorMap <- The main picture itself
// NormalMap <- Picture parameter
// SpecularMap <- Picture parameter

// LightPosition
// LightColor
// LightAttenuation

// AmbientColor
// AmbientDepth
// AmbientAttenuation

// SpecularColor
// SpecularDepth
// SpecularAttenuation

// Active

const std::string	InitialDeclaration =
  "varying vec2 vClip;\n"
  "varying vec4 vColor;\n"
  ""
  "uniform vec2 WindowSize;\n"
  "uniform sampler2D ColorMap;\n"
  "uniform sampler2D NormalMap;\n"
  "uniform sampler2D SpecularMap;\n"
  "\n"
  ;

const std::string	StretchedDeclaration =
  "uniform vec3 LightPosition%d;\n"
  "uniform vec4 LightColor%d;\n"
  "uniform float LightAttenuation%d;\n"
  "\n"
  "uniform vec4 AmbientColor%d;\n"
  "uniform float AmbientDepth%d;\n"
  "uniform float AmbientAttenuation%d;\n"
  "\n"
  "uniform vec4 SpecularColor%d;\n"
  "uniform float SpecularDepth%d;\n"
  "uniform float SpecularAttenuation%d;\n"
  "\n"
  "uniform float Active%d;\n"
  "\n"
  ;

const std::string	BodyStart =
  "void main()\n"
  "{\n"
  "  vec2 Coord = gl_TexCoord[0].xy;\n"
  "\n"
  "  vec2 LPos;\n"
  "  vec2 SpecularPosition;\n"
  "  vec4 DiffuseColor = texture2D(ColorMap, Coord);\n"
  "  vec4 NormalColor = texture2D(NormalMap, Coord);\n"
  "  vec4 SpecularColor = texture2D(SpecularMap, Coord);\n"
  "  vec3 Normal = normalize(NormalColor * 2.0 - 1.0).rgb;\n"
  "  vec4 Specular = normalize(SpecularColor * 2.0 - 1.0);\n"
  "\n"
  "  vec2 PositionOnScreen;\n"
  "  vec2 ReversedPositionOnScreen;\n"
  "  vec3 DistanceOnScreen;\n"
  "  vec3 Direction;\n"
  "  float DotNormalDirection;\n"
  "  float ColorStrength;\n"
  "  float D;\n"
  "  float Attenuation;\n"
  "  vec3 UserCamera = vec3(0.0, 0.0, 2.0);\n"
  "\n"
  "  vec3 AmbientResult;\n"
  "  vec3 LightResult;\n"
  "  vec3 SpecularResult;\n"
  "  vec3 AllResult = vec3(0.0, 0.0, 0.0);\n"
  ;

const std::string	StretchedBody =
  "  // Active\n"
  "  if (Active%d > 0.5)\n"
  "  {\n"
  "    LPos = LightPosition%d.xy;\n"
  "    PositionOnScreen = (LPos.xy - gl_FragCoord.xy) / WindowSize.xy;"
  "    LPos.y = WindowSize.y - LPos.y;"
  "    ReversedPositionOnScreen = (LPos.xy - gl_FragCoord.xy) / WindowSize.xy;"
  "\n"
  // Compute spot light
  "    DistanceOnScreen = vec3(PositionOnScreen, LightPosition%d.z);\n"
  "    Direction = normalize(DistanceOnScreen);\n"
  "    DotNormalDirection = dot(Normal, Direction);\n"
  "    ColorStrength = clamp(DotNormalDirection, 0.0, 1.0);\n"
  "    D = LightAttenuation%d * length(DistanceOnScreen);\n"
  "    Attenuation = 1.0 / (0.5 + 0.5 * D + 0.5 * D * D);\n"
  "    LightResult = Attenuation * LightColor%d.rgb * LightColor%d.a * ColorStrength;\n"
  "\n"
  // Compute ambient light
  "    DistanceOnScreen = vec3(PositionOnScreen.x, ReversedPositionOnScreen.y, AmbientDepth%d);\n"
  "    D = AmbientAttenuation%d * length(DistanceOnScreen);\n"
  "    Attenuation = 1.0 / (0.5 + 0.5 * D + 0.5 * D * D);\n"
  "    AmbientResult = Attenuation * AmbientColor%d.rgb * AmbientColor%d.a;\n"
  "\n"
  // Compute specular light
  "    SpecularPosition = PositionOnScreen; // vec2(PositionOnScreen.x, WindowSize.y - PositionOnScreen.y);\n"
  "    DistanceOnScreen = vec3(SpecularPosition, SpecularDepth%d);\n"
  "    Direction = normalize(DistanceOnScreen);\n"
  "    DotNormalDirection = dot(Normal, Direction);\n"
  "    D = SpecularAttenuation%d * length(DistanceOnScreen);\n"
  "    Attenuation = 1.0 / (0.5 + 0.5 * D + 0.5 * D * D);\n"

  "    if (DotNormalDirection < 0.0)\n"
  "      SpecularResult = vec3(0.0, 0.0, 0.0);\n"
  "    else\n"
  "      SpecularResult = Attenuation * SpecularColor%d.rgb * Specular.rgb * pow(max(0.0, dot(reflect(-Direction, Normal), UserCamera)), Specular.a);\n"
  "\n"
  "    AllResult += (LightResult + SpecularResult + AmbientResult) * DiffuseColor.rgb;\n"
  "  }\n"
  ;

const std::string	BodyEnd =
  "  gl_FragColor = gl_Color * vec4(AllResult, DiffuseColor.a);\n"
  "}\n"
  ;

static void		_clean_shader(void)
{
  if (gl_normal_map_shader)
    {
      bunny_delete_shader(gl_normal_map_shader);
      gl_normal_map_shader = NULL;
    }
}

t_bunny_shader		*bunny_normal_map_shader(const t_bunny_normal_map	*nm)
{
  char			buffer[4096];
  unsigned int		i;

  if (nm == NULL)
    {
      if (gl_normal_map_shader)
        bunny_delete_shader(gl_normal_map_shader);
      gl_normal_map_shader = NULL;
      return (NULL);
    }
  if (gl_normal_map_shader == NULL)
    {
      std::stringstream	ss;

      if ((gl_normal_map_shader = bunny_new_shader()) == NULL)
	return (NULL);

      ss << InitialDeclaration;
      for (i = 0; i < sizeof(nm->lights) / sizeof(nm->lights[0]); ++i)
	{
	  snprintf(&buffer[0], sizeof(buffer), StretchedDeclaration.c_str(),
		   i, i, i, i, i, i, i, i, i, i, i); // 1$?
	  ss << &buffer[0];
	}
      ss << BodyStart;
      for (i = 0; i < sizeof(nm->lights) / sizeof(nm->lights[0]); ++i)
	{
	  snprintf(&buffer[0], sizeof(buffer), StretchedBody.c_str(),
		   i, i, i, i, i, i, i, i, i, i, i, i, i); // 1$?
	  ss << &buffer[0];
	}
      ss << BodyEnd;

      if (bunny_read_shader(gl_normal_map_shader, NULL, ss.str().c_str()) == false)
	return (NULL);
      atexit(_clean_shader);
    }

  bunny_shader_set_variable
    (gl_normal_map_shader,
     "ColorMap",
     BVT_CURRENT_TEXTURE_TYPE
     );

  bunny_shader_set_variable
    (gl_normal_map_shader,
     "WindowSize",
     BVT_2_FLOAT,
     (double)nm->window_size.x,
     (double)nm->window_size.y
     );

  bunny_shader_set_variable
    (gl_normal_map_shader,
     "NormalMap",
     BVT_PICTURE,
     nm->normal_map
     );

  bunny_shader_set_variable
    (gl_normal_map_shader,
     "SpecularMap",
     BVT_PICTURE,
     nm->specular_map
     );

  for (i = 0; i < sizeof(nm->lights) / sizeof(nm->lights[0]); ++i)
    {
      snprintf(&buffer[0], sizeof(buffer), "Active%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_1_FLOAT,
	 (double)(nm->lights[i].active ? 2.0 : -1.0)
	 );

      snprintf(&buffer[0], sizeof(buffer), "LightPosition%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_3_FLOAT,
	 (double)nm->lights[i].x,
	 (double)nm->lights[i].y,
	 (double)nm->lights[i].z
	 );
      snprintf(&buffer[0], sizeof(buffer), "LightColor%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_FULL_COLOR,
	 nm->lights[i].light_color.full
	 );
      snprintf(&buffer[0], sizeof(buffer), "LightAttenuation%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_1_FLOAT,
	 (double)nm->lights[i].light_attenuation
	 );
      snprintf(&buffer[0], sizeof(buffer), "AmbientColor%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_FULL_COLOR,
	 nm->lights[i].ambient_color.full
	 );
      snprintf(&buffer[0], sizeof(buffer), "AmbientDepth%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_1_FLOAT,
	 (double)nm->lights[i].ambient_depth
	 );
      snprintf(&buffer[0], sizeof(buffer), "AmbientAttenuation%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_1_FLOAT,
	 (double)nm->lights[i].ambient_attenuation
	 );
      snprintf(&buffer[0], sizeof(buffer), "SpecularColor%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_FULL_COLOR,
	 nm->lights[i].specular_color.full
	 );
      snprintf(&buffer[0], sizeof(buffer), "SpecularDepth%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_1_FLOAT,
	 (double)nm->lights[i].specular_depth
	 );
      snprintf(&buffer[0], sizeof(buffer), "SpecularAttenuation%d", i);
      bunny_shader_set_variable
	(gl_normal_map_shader,
	 &buffer[0],
	 BVT_1_FLOAT,
	 (double)nm->lights[i].specular_attenuation
	 );
    }

  return (gl_normal_map_shader);
}

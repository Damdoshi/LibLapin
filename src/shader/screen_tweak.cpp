// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2015
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static t_bunny_shader	*gl_screen_tweak_shader = NULL;

static const std::string gl_screen_tweak_code =
#include		"screen_tweak.frag"
  ;

static void		_clean_shader(void)
{
  bunny_delete_shader(gl_screen_tweak_shader);
}

t_bunny_shader		*bunny_screen_tweak_shader(const t_bunny_screen_tweak *bst)
{
  if (gl_screen_tweak_shader == NULL)
    {
      if ((gl_screen_tweak_shader = bunny_new_shader()) == NULL)
	return (NULL);
      if (bunny_read_shader
	  (gl_screen_tweak_shader, NULL, gl_screen_tweak_code.c_str()) == false)
	return (NULL);
      atexit(_clean_shader);
    }

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "Picture",
     BVT_CURRENT_TEXTURE_TYPE
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "Luminosity",
     BVT_1_FLOAT,
     bst->luminosity
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "Red",
     BVT_1_FLOAT,
     bst->color.argb[RED_CMP] / 255.0
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "Green",
     BVT_1_FLOAT,
     bst->color.argb[GREEN_CMP] / 255.0
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "Blue",
     BVT_1_FLOAT,
     bst->color.argb[BLUE_CMP] / 255.0
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "InvertColor",
     BVT_1_FLOAT,
     bst->invert_color ? 1.0 : 0.0
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "GrayScale",
     BVT_1_FLOAT,
     bst->gray_scale ? 1.0 : 0.0
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "BlackNWhite",
     BVT_1_FLOAT,
     bst->black_white ? 1.0 : 0.0
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "ColorBlind",
     BVT_1_FLOAT,
     (double)bst->color_blind
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "Blur",
     BVT_1_FLOAT,
     bst->blur_level * 0.0004f
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "NoiseColor",
     BVT_1_FLOAT,
     (double)bst->noise_color
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "NoiseType",
     BVT_1_FLOAT,
     (double)bst->noise_type
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "NoiseStrenght",
     BVT_1_FLOAT,
     bst->noise_strenght
     );

  bunny_shader_set_variable
    (gl_screen_tweak_shader,
     "Random",
     BVT_1_FLOAT,
     (double)((rand() % (int)1e6) / 1e6 + 1.0 / 1e6)
     );

  return (gl_screen_tweak_shader);
}


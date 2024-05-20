// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2021
//
// Bibliothèque Lapin

#include		"lapin_private.h"

static t_bunny_shader	*gl_blur_shader = NULL;

static const std::string gl_blur_code =
#include		"blur.frag"
  ;

static void		_clean_shader(void)
{
  if (gl_blur_shader)
    {
      bunny_delete_shader(gl_blur_shader);
      gl_blur_shader = NULL;
    }
}

t_bunny_shader		*bunny_blur_shader(const t_bunny_blur *b)
{
  if (b == NULL)
    {
      _clean_shader();
      return (NULL);
    }
  if (gl_blur_shader == NULL)
    {
      if ((gl_blur_shader = bunny_new_shader()) == NULL)
	return (NULL);
      if (bunny_read_shader
	  (gl_blur_shader, NULL, gl_blur_code.c_str()) == false)
	{
	  _clean_shader();
	  return (NULL);
	}
      atexit(_clean_shader);
    }

  bunny_shader_set_variable
    (gl_blur_shader,
     "source",
     BVT_CURRENT_TEXTURE_TYPE
     );

  bunny_shader_set_variable
    (gl_blur_shader,
     "offsetFactor",
     BVT_2_FLOAT,
     b->offset_factor.x,
     b->offset_factor.y
     );

  return (gl_blur_shader);
}

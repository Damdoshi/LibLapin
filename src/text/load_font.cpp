// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include			<string.h>
#include			"lapin_private.h"

#define				PATTERN		"%u width, %u height, %s file, %p (%d, %d) size -> %p"

t_bunny_font			*bunny_load_font(unsigned int		width,
						 unsigned int		height,
						 const char		*file,
						 const t_bunny_position	*size)
{
  t_bunny_font			*final;

  if (bunny_which_format(file) != BC_CUSTOM)
    {
      final = NULL;
      if (bunny_set_font_attribute(file, &final, NULL) == false)
	return (NULL);
      return (final);
    }
  else if (strstr(file, ".ttf"))
    final = __bunny_load_ttf(width, height, file, size);
  else
    final = __bunny_load_gfx(width, height, file, size);
  if (final == NULL)
    scream_error_if
      (return (NULL), bunny_errno, PATTERN, "ressource,text", width, height, file, size, size->x, size->y, (void*)NULL);

  // Clipable properties
  final->clipable.buffer.width = width;
  final->clipable.buffer.height = height;
  final->clipable.clip_x_position = 0;
  final->clipable.clip_y_position = 0;
  final->clipable.clip_width = width;
  final->clipable.clip_height = height;
  final->clipable.position.x = 0;
  final->clipable.position.y = 0;
  final->clipable.origin.x = 0;
  final->clipable.origin.y = 0;
  final->clipable.scale.x = 1;
  final->clipable.scale.y = 1;
  final->clipable.rotation = 0;
  final->clipable.color_mask.full = WHITE;
  final->clipable.smooth = false;
  final->clipable.mosaic = false;
  ((struct bunny_ttf_font*)final)->glactive = false;

  // Text properties
  final->string = NULL;
  final->string_offset = 0;
  final->string_len = (size_t)-1;
  final->halign = BAL_LEFT;
  final->valign = BAL_TOP;
  final->outline = 0;
  final->outline_size = 0;
  final->color = WHITE;
  final->offset.x = 0;
  final->offset.y = 0;
  final->interglyph_space.x = 0;
  final->interglyph_space.y = 0;

  scream_log_if(PATTERN, "ressource,text", width, height, file, size, size->x, size->y, final);
  return (final);
}

t_bunny_font			*bunny_read_textbox(t_bunny_configuration *cnf)
{
  t_bunny_font			*f;

  if (bunny_set_font_attribute(NULL, &f, &cnf) == false)
    return (NULL);
  return (f);
}

t_bunny_font			*bunny_load_text(const char		*file)
{
  return (bunny_load_font(0, 0, file, NULL));
}


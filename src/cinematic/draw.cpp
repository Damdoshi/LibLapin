// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin librarye

#include		"lapin_private.h"

void			__bunny_draw_cinematic(struct bunny_cinematic	*cin)
{
  t_bunny_map		**node;
  t_bunny_sprite	*pic;

  if (cin->background_color.argb[ALPHA_CMP] != 0)
    bunny_fill((t_bunny_buffer*)cin, cin->background_color.full);
  
  for (bunny_map_all(cin->pictures, node))
    {
      pic = bunny_map_data(*node, t_bunny_sprite*);
      if (!pic->clipable.color_mask.argb[ALPHA_CMP])
	continue ;
      bunny_sprite_animate_now(pic);
      bunny_blit((t_bunny_buffer*)cin, &pic->clipable, NULL);
    }

  if (cin->foreground_color.argb[ALPHA_CMP] != 0)
    bunny_fill((t_bunny_buffer*)cin, cin->foreground_color.full);
}

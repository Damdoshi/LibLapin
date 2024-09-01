// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
//
// Lapin librarye

#include		"lapin_private.h"

void			__bunny_draw_cinematic(struct bunny_cinematic	*cin)
{
  t_bunny_map		**node;
  t_bunny_sprite	*pic;
  t_bunny_font		*fnt;

  // Couleur de fond
  if (cin->background_color.argb[ALPHA_CMP] != 0)
    bunny_fill((t_bunny_buffer*)cin, cin->background_color.full);

  // On affiche les images
  for (bunny_map_all(cin->pictures, node))
    {
      pic = bunny_map_data(*node, t_bunny_sprite*);
      if (!pic->clipable.color_mask.argb[ALPHA_CMP])
	continue ;
      bunny_blit((t_bunny_buffer*)cin, &pic->clipable, NULL);
    }

  // On affiche les textes
  for (bunny_map_all(cin->fonts, node))
    {
      fnt = bunny_map_data(*node, t_bunny_font*);
      if (!fnt->string || !*fnt->string || !fnt->string_len)
	continue ;
      bunny_clear(&fnt->clipable.buffer, 0);
      bunny_draw(&fnt->clipable);
      bunny_blit((t_bunny_buffer*)cin, &fnt->clipable, NULL);
    }

  // Couleur avant (flash, brouillard, etc.)
  if (cin->foreground_color.argb[ALPHA_CMP] != 0)
    bunny_fill((t_bunny_buffer*)cin, cin->foreground_color.full);
}

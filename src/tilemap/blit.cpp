// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include		"lapin_private.h"

void			__bunny_blit_flat_tilemap(struct bunny_tilemap		*tmap,
						  const t_bunny_clipable	*p,
						  const t_bunny_position	*pos,
						  const t_bunny_shader		*shader);

void			__bunny_blit_layer_tilemap(struct bunny_tilemap		*tmap,
						   const t_bunny_clipable	*p,
						   const t_bunny_position	*pos,
						   const t_bunny_shader		*shader);

void			__bunny_blit_vector_tilemap(struct bunny_tilemap	*tmap,
						    const t_bunny_clipable	*p,
						    const t_bunny_position	*pos,
						    const t_bunny_shader	*shader)
{
  (void)tmap;
  (void)p;
  (void)pos;
  (void)shader;
}

void			__bunny_blit_tilemap(struct bunny_tilemap	*tmap,
					     const t_bunny_clipable	*_pic,
					     const t_bunny_position	*_pos,
					     const t_bunny_shader	*shader)
{
  (void)tmap;
  (void)_pic;
  (void)_pos;
  (void)shader;
  //__bunny_blit_flat_tilemap(tmap, _pic, _pos, shader);
  /*
    if (tmap->method == BTM_FLAT)
    __bunny_blit_flat_tilemap(tmap, _pic, _pos, shader);
    else if (tmap->method == BTM_LAYER)
    __bunny_blit_layer_tilemap(tmap, _pic, _pos, shader);
    else if (tmap->method == BTM_VECTOR)
    __bunny_blit_vector_tilemap(tmap, _pic, _pos, shader);
  */
}


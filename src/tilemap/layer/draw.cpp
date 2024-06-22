// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Lapin library

#include	"lapin_private.h"

// On dessine sur pic a la position pos le dessin venant de tset
static void	draw_tile(t_bunny_picture				*tset,
			  t_bunny_picture				*pic,
			  t_bunny_position				&target,
			  const t_bunny_area				&clip)
{
  tset->clip_x_position = clip.x;
  tset->clip_y_position = clip.y;
  tset->clip_width = clip.w;
  tset->clip_height = clip.h;
  target.x *= tset->clip_width;
  target.y *= tset->clip_height;
  bunny_blit(&pic->buffer, tset, &target);
}

// On rafraichit la liste de tuile qu'on a recu.
// Chaque dessin efface la tuile precedemment effacée
static void	refresh_tiles(struct bunny_tilemap			*tmap,
			      t_bunny_zposition				*trtile,
			      int					max)
{
  for (int i = 0; i < max; ++i)
    {
      int		x = trtile[i].x;
      int		y = trtile[i].y;
      int		z = trtile[i].z;

      t_bunny_area	clip{x, y, tmap->tile_size.x, tmap->tile_size.y};
      t_bunny_position	pos{x, y};
      int		til = tmap->layers[z].tiles[x + y * tmap->map_size.x];
      t_bunny_tileset	*ts = bunny_get_tileset_for_tile((t_bunny_tilemap*)tmap, til);
      t_bunny_picture	*strata;

      strata = tmap->layers[z].picture;
      strata->clip_x_position = clip.x;
      strata->clip_y_position = clip.y;
      strata->clip_width = clip.w;
      strata->clip_height = clip.h;
      bunny_clear(&strata->buffer, 0); // Fully transparent
      draw_tile(ts->tileset, strata, pos, clip); // Redraw the tile
    }
}

// Draw est appellé après qu'on ai blitté des éléments dessus, il
// sert a rendre dans working ce qu'on est censé voir.
bool		__bunny_draw_layer_tilemap(struct bunny_tilemap		*tmap)
{
  int		i;

  if (tmap->rendered == false)
    {
      // Remplissage initial. Une fois que c'est fait, le seul moyen de changer, c'est de passer
      // par changed_tiles.
      for (i = 0; i < tmap->nbr_layers; ++i)
	{
	  for (int y = 0; y < tmap->map_size.y; ++y)
	    for (int x = 0; x < tmap->map_size.x; ++x)
	      {
		t_bunny_area	clip{x, y, tmap->tile_size.x, tmap->tile_size.y};
		t_bunny_position pos{x, y};
		int		til = tmap->layers[i].tiles[x + y * tmap->map_size.x];

		if (til == 0)
		  continue ;
		t_bunny_tileset	*ts = bunny_get_tileset_for_tile((t_bunny_tilemap*)tmap, til);
		t_bunny_picture	*pic = ts->tileset;

		if (ts->animated_tiles_id != NULL && ts->animated_tiles_id[til] != NULL)
		  {
		    t_bunny_zposition &zpos = tmap->animated_tiles[tmap->nbr_animated_tiles++];

		    pic = &ts->animated_tiles_id[til]->clipable;
		    clip.x = pic->clip_x_position;
		    clip.y = pic->clip_y_position;
		    zpos.x = x;
		    zpos.y = y;
		    zpos.z = i;
		  }
		draw_tile(pic, tmap->layers[i].picture, pos, clip);
	      }
	}
      tmap->rendered = true;
    }
  // Boucle d'animation des tuiles animées
  refresh_tiles(tmap, &tmap->animated_tiles[0], tmap->nbr_animated_tiles);
  refresh_tiles(tmap, &tmap->changed_tiles[0], tmap->nbr_changed_tiles);

  // On dessine dans la surface du clipable final les couches demandées
  int	depth = bunny_clamp(tmap->layer_clip[0], 0, tmap->nbr_layers - 1);
  int	surface = bunny_clamp(tmap->layer_clip[1], 0, tmap->nbr_layers - 1);
  int	rpt = 3; // repetition of each layer
  //double ratio = 10;
  t_bunny_position pos = {tmap->working->buffer.width / 2, tmap->working->buffer.height / 2};

  for (int layer = depth * rpt; layer <= surface * rpt; ++layer)
    {
      tmap->layers[layer / rpt].picture->origin.x = tmap->camera.x;
      tmap->layers[layer / rpt].picture->origin.y = tmap->camera.y;
      //tmap->layers[layer / rpt].picture->scale.x = (1 + (layer * rpt) / ratio) * tmap->zoom.x;
      //tmap->layers[layer / rpt].picture->scale.y = (1 + (layer * rpt) / ratio) * tmap->zoom.y;
      // = ratio / (depth - (double)tmap->camera.z / rpt);
      bunny_blit(&tmap->working->buffer, tmap->layers[layer / rpt].picture, &pos);
    }

  ((bunny_picture*)tmap->working)->texture->display();
  return (true);
}


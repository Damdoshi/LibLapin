// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include	"lapin_private.h"

#define		PATTERN		"%p configuration, %p tilemap -> %p"

t_bunny_tilemap *__bunny_load_dabsic_tilemap(t_bunny_configuration	*conf,
					     struct bunny_tilemap	*tmap)
{
  const char		*tmp;
  const char		*res;
  t_bunny_configuration *tmnode;
  t_bunny_configuration *tiles;
  size_t		len;
  size_t		i, j;
  int			first_tile;
  int			tmpi;

  if (bunny_configuration_getf_node(conf, &tmnode, "TileMap") == false)
    goto SingleFailure;

  if (!bunny_configuration_getf_int(tmnode, &tmap->map_size.x, "MapSize[0]") ||
      !bunny_configuration_getf_int(tmnode, &tmap->map_size.y, "MapSize[1]"))
    goto SingleFailure;

  if (!bunny_configuration_getf_int(tmnode, &tmap->nbr_layers, "MapSize[2]"))
    bunny_configuration_getf_int(tmnode, &tmap->nbr_layers, "Layers[0]");

  if (bunny_configuration_casesf(tmnode, "Tiles")
      != (ssize_t)(len = tmap->map_size.x * tmap->map_size.y * tmap->nbr_layers))
    goto SingleFailure;

  if ((tmap->tiles = (int*)bunny_malloc(sizeof(*tmap->tiles) * len)) == NULL)
    goto SingleFailure;

  for (i = 0; i < len; ++i)
    if (!bunny_configuration_getf_int(tmnode, &tmap->tiles[i], "Tiles[%zu]", i))
      goto DeleteTiles;

  if (!bunny_configuration_getf_int(tmnode, &tmap->tile_size.x, "TileSize[0]") ||
      !bunny_configuration_getf_int(tmnode, &tmap->tile_size.y, "TileSize[1]"))
    goto DeleteTiles;

  if ((tmap->nbr_tilesets = bunny_configuration_casesf(tmnode, "TileSets")) < 1)
    goto DeleteTiles;

  if (!(tmap->tilesets = (t_bunny_tileset*)bunny_calloc(tmap->nbr_tilesets, sizeof(*tmap->tilesets))))
    goto DeleteTiles;

  first_tile = 1;
  for (i = 0; i < tmap->nbr_tilesets; ++i)
    {
      t_bunny_tileset	*tset = &tmap->tilesets[i];

      if (!bunny_configuration_getf_node(tmnode, &tiles, "TileSets[%zu]", i))
	goto DeleteTileSets;

      // Full description
      if (bunny_configuration_getf_string(tiles, &tmp, "RessourceFile"))
	{
	  res = tmp;
	  if (bunny_set_clipable_attribute
	      (NULL, &tset->tileset, &tiles, BCT_PICTURE) == false)
	    goto DeleteTileSets;
	}
      // External file
      else if (bunny_configuration_getf_string(tiles, &tmp, "."))
	{
	  res = tmp;
	  if ((tset->tileset = bunny_load_picture(tmp)) == NULL)
	    goto DeleteTileSets;
	}
      else
	goto DeleteTileSets;

      if (!bunny_configuration_getf_int(tiles, &tset->tile_size.x, "TileSize[0]"))
	goto DeleteTileSets;
      if (!bunny_configuration_getf_int(tiles, &tset->tile_size.y, "TileSize[1]"))
	goto DeleteTileSets;

      bunny_configuration_getf_int(tiles, &tset->intertile.x, "InterTile[0]");
      bunny_configuration_getf_int(tiles, &tset->intertile.y, "InterTile[1]");

      tmap->tilesets[i].tileset->clip_width = tmap->tilesets[i].tile_size.x;
      tmap->tilesets[i].tileset->clip_height = tmap->tilesets[i].tile_size.y;

      tmap->tilesets[i].tileset_size.x =
	tmap->tilesets[i].tileset->buffer.width /
	tmap->tilesets[i].tileset->clip_width;
      tmap->tilesets[i].tileset_size.y =
	tmap->tilesets[i].tileset->buffer.height /
	tmap->tilesets[i].tileset->clip_height;

      tset->nbr_animated_tiles = bunny_configuration_casesf(tiles, "AnimatedTiles");

      if ((tset->animated_tiles = (t_bunny_sprite**)bunny_calloc
	   (tset->nbr_animated_tiles, sizeof(*tset->animated_tiles))) == NULL)
	goto DeleteTileSets;

      for (j = 0; j < tset->nbr_animated_tiles; ++j)
	{
	  t_bunny_configuration *nod;
	  struct bunny_sprite *spr;

	  if (!bunny_configuration_getf_node(tiles, &nod, "AnimatedTiles[%zu]", j))
	    goto DeleteTileSets;
	  if ((tset->animated_tiles[j] =
	       (t_bunny_sprite*)(spr = _bunny_new_sprite())) == NULL)
	    goto DeleteTileSets;
	  spr->texture = ((struct bunny_picture*)tset->tileset)->texture;
	  spr->res_id = ((struct bunny_picture*)tset->tileset)->res_id;
	  spr->tex = &spr->texture->getTexture();
	  spr->sprite->setTexture(*spr->tex);
	  if (RessourceManager.disable_manager == false)
	    RessourceManager.AddToPool
	      (ResManager::SF_RENDERTEXTURE, res, spr->res_id, spr, spr->texture);

	  spr->type = SPRITE;
	  spr->width = spr->tex->getSize().x;
	  spr->height = spr->tex->getSize().y;

	  spr->rect.x = 0;
	  spr->rect.y = 0;
	  spr->rect.w = tset->tileset->clip_width;
	  spr->rect.h = tset->tileset->clip_height;

	  spr->position.x = 0;
	  spr->position.y = 0;
	  spr->origin.x = 0;
	  spr->origin.y = 0;
	  spr->scale.x = 1;
	  spr->scale.y = 1;
	  spr->rotation = 0;
	  spr->color_mask.full = WHITE;

	  if (bunny_set_clipable_attribute
	      (NULL, (t_bunny_clipable**)&spr, &nod, BCT_SPRITE) == false)
	    goto DeleteTileSets;
	  if (_bunny_set_sprite_attribute
	      (*spr, *(SmallConf*)nod) == false)
	    goto DeleteTileSets;
	}

      tset->nbr_tiles = tset->tileset_size.x * tset->tileset_size.y;
      tset->last_tile = first_tile + tset->nbr_animated_tiles + tset->nbr_tiles - 1;
    }

  bunny_configuration_getf_double(tmnode, &tmap->camera.x, "Camera[0]");
  bunny_configuration_getf_double(tmnode, &tmap->camera.y, "Camera[1]");

  bunny_configuration_getf_double(tmnode, &tmap->zoom.x, "Zoom[0]");
  bunny_configuration_getf_double(tmnode, &tmap->zoom.y, "Zoom[1]");

  bunny_configuration_getf_double(tmnode, &tmap->tile_rotation, "Rotation");

  bunny_configuration_getf_int(tmnode, &tmap->layer_clip[0], "LayerClip[0]");
  bunny_configuration_getf_int(tmnode, &tmap->layer_clip[1], "LayerClip[1]");

  tmpi = false;
  if (bunny_configuration_getf_int(tmnode, &tmpi, "LockBorders") && tmpi)
    tmap->lock_borders = true;
  tmpi = false;
  if (bunny_configuration_getf_int(tmnode, &tmpi, "Loop[0]") && tmpi)
    tmap->loop[0] = true;
  tmpi = false;
  if (bunny_configuration_getf_int(tmnode, &tmpi, "Loop[1]") && tmpi)
    tmap->loop[1] = true;

  return ((t_bunny_tilemap*)tmap);

 DeleteTileSets:
  for (i = 0; i < tmap->nbr_tilesets; ++i)
    {
      if (tmap->tilesets[i].tileset)
	bunny_delete_clipable(tmap->tilesets[i].tileset);
      if (tmap->tilesets[i].animated_tiles)
	for (j = 0; j < tmap->tilesets[i].nbr_animated_tiles; ++j)
	  if (tmap->tilesets[i].animated_tiles[j])
	    bunny_delete_clipable(&tmap->tilesets[i].animated_tiles[j]->clipable);
    }
  bunny_free(tmap->tilesets);
 DeleteTiles:
  bunny_free(tmap->tiles);
 SingleFailure:
  return (NULL);
}

// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p configuration, %p tilemap -> %p"

static bool		load_properties(t_bunny_configuration			*cnf,
					t_bunny_map				**_map)
{
  t_bunny_configuration	*props;
  t_bunny_map		*map;

  if ((map = *_map = bunny_new_map(string_map)) == NULL)
    return (false);
  for (bunny_configuration_all_children(cnf, props))
    {
      const char	*k, *d;

      k = bunny_configuration_get_name(props);
      if (strcmp(k, "Id") == 0)
	continue ;
      if (!bunny_configuration_getf_string(props, &d, "."))
	goto DeleteMap;
      if (!(d = bunny_strdup(d)))
	goto DeleteMap;
      if (bunny_string_map_set(map, k, d) == NULL)
	{
	  bunny_free((char*)d);
	  goto DeleteMap;
	}
    }

  return (true);

 DeleteMap:
  t_bunny_map		**nodmap;

  for (bunny_map_all(map, nodmap))
    bunny_free(bunny_map_data(*nodmap, char*));
  bunny_delete_map(map);
  return (false);
}

static bool		load_tileset(t_bunny_configuration			*cnf,
				     struct bunny_tilemap			*tmap,
				     t_bunny_tileset				*ts)
{
  int			i, j;

  if (!bunny_configuration_getf_string(cnf, &ts->name, "Name"))
    ts->name = "";

  // Tile info
  if (!bunny_configuration_getf_int(cnf, &ts->tile_size.x, "TileWidth"))
    if (!bunny_configuration_getf_int(cnf, &ts->tile_size.x, "Width"))
      if (!bunny_configuration_getf_int(cnf, &ts->tile_size.x, "TileSize[0]"))
	ts->tile_size.x = tmap->tile_size.x;
  if (!bunny_configuration_getf_int(cnf, &ts->tile_size.y, "TileHeight"))
    if (!bunny_configuration_getf_int(cnf, &ts->tile_size.y, "Height"))
      if (!bunny_configuration_getf_int(cnf, &ts->tile_size.y, "TileSize[1]"))
       	ts->tile_size.y = tmap->tile_size.y;

  // Intertile
  bunny_configuration_getf_int(cnf, &ts->intertile.x, "Intertile[0]");
  bunny_configuration_getf_int(cnf, &ts->intertile.y, "Intertile[1]");
  bunny_configuration_getf_int(cnf, &ts->margin.x, "Intertile[0]");
  bunny_configuration_getf_int(cnf, &ts->margin.y, "Intertile[1]");

  // Misc
  if (!(ts->name = bunny_strdup(ts->name)))
    return (false);

  // Picture
  const char		*tmp = NULL;
  t_bunny_configuration	*pic;

  if (!bunny_configuration_getf_string(cnf, &tmp, "RessourceFile"))
    {
      if (!bunny_configuration_getf_node(cnf, &pic, "Picture"))
	goto DeleteName;
      else if (!bunny_set_clipable_attribute("", &ts->tileset, &pic, BCT_PICTURE))
	goto DeleteName;
    }
  else if (!(ts->tileset = bunny_load_picture(tmp)))
    goto DeleteName;

  // Last values
  // First and last tiles if not set here will be set un the parent function.
  if (!bunny_configuration_getf_int(cnf, &ts->first_tile, "FirstTileId"))
    ts->first_tile = -1;
  ts->tileset_size.x = ts->tileset->buffer.width / ts->tile_size.x;
  ts->tileset_size.y = ts->tileset->buffer.height / ts->tile_size.y;
  if (!bunny_configuration_getf_int(cnf, &ts->nbr_tiles, "TileCount"))
    ts->nbr_tiles = ts->tileset_size.x * ts->tileset_size.y;

  // Load animated tiles
  ts->nbr_animated_tiles = bunny_configuration_casesf(cnf, "AnimatedTiles");
  if (!(ts->animated_tiles_id = (t_bunny_sprite**)bunny_calloc
	(ts->nbr_tiles, sizeof(*ts->animated_tiles))))
    goto DeletePicture;
  if (!(ts->animated_tiles = (t_bunny_sprite**)bunny_calloc
	(ts->nbr_animated_tiles, sizeof(*ts->animated_tiles))))
    goto DeletePicture;
  for (i = 0; i < ts->nbr_animated_tiles; ++i)
    {
      int		id;

      if (!bunny_configuration_getf_int(cnf, &id, "AnimatedTiles[%d].LocalId", i) || id <= 0)
	goto DeleteAnimatedTiles;
      // Set the picture file so bunny_load_sprite works correctly
      if (tmp == NULL)
	if (!bunny_configuration_getf_string(cnf, &tmp, "Picture.RessourceFile"))
	  goto DeleteAnimatedTiles;
      if (!bunny_configuration_getf_string(cnf, NULL, "AnimatedTiles[%d].RessourceFile", i))
	bunny_configuration_setf_string(cnf, tmp, "AnimatedTiles[%d].RessourceFile", i);

      if (!bunny_configuration_getf_int(cnf, NULL, "AnimatedTiles[%d].Clip.Size[0]", i))
	bunny_configuration_setf_int(cnf, ts->tile_size.x, "AnimatedTiles[%d].Clip.Size[0]", i);
      if (!bunny_configuration_getf_int(cnf, NULL, "AnimatedTiles[%d].Clip.Size[1]", i))
	bunny_configuration_setf_int(cnf, ts->tile_size.y, "AnimatedTiles[%d].Clip.Size[1]", i);

      if (!bunny_configuration_getf_int(cnf, NULL, "AnimatedTiles[%d].Intertile[0]", i))
	bunny_configuration_setf_int(cnf, ts->intertile.x, "AnimatedTiles[%d].Intertile[0]", i);
      if (!bunny_configuration_getf_int(cnf, NULL, "AnimatedTiles[%d].Intertile[1]", i))
	bunny_configuration_setf_int(cnf, ts->intertile.y, "AnimatedTiles[%d].Intertile[1]", i);

      bunny_configuration_getf_node(cnf, &pic, "AnimatedTiles[%d]", i);
      if (!(ts->animated_tiles[i] = bunny_read_sprite(pic)))
	goto DeleteAnimatedTiles;
      if (ts->animated_tiles_id[id])
	goto DeleteAnimatedTiles;
      ts->animated_tiles_id[id] = ts->animated_tiles[i];
    }

  // Custom properties
  if (bunny_configuration_getf_node(cnf, &pic, "Properties"))
    if (!load_properties(pic, &ts->properties))
      goto DeleteAnimatedTiles;

  // Tile custom properties
  if (!(ts->tile_properties_id = (t_bunny_tile_property*)bunny_calloc
	(ts->nbr_tiles, sizeof(*ts->tile_properties_id))))
    goto DeleteProperties;
  for (i = 0; bunny_configuration_getf_node(cnf, &pic, "TileProperties[%d]", i); ++i)
    {
      int		til;

      if (!bunny_configuration_getf_int(pic, &til, "Id"))
	goto DeleteTileProperties;
      if (til < 0 || til >= ts->nbr_tiles)
	goto DeleteTileProperties;
      if (ts->tile_properties_id[til].properties)
	goto DeleteTileProperties; // Already set.
      if (!load_properties(pic, &ts->tile_properties_id[til].properties))
	goto DeleteTileProperties;
      ts->nbr_tile_properties += 1;
    }
  if (!(ts->tile_properties = (t_bunny_tile_property**)bunny_calloc
	(ts->nbr_tile_properties, sizeof(*ts->tile_properties))))
    goto DeleteTileProperties;
  for (i = j = 0; i < ts->nbr_tiles; ++i)
    if (ts->tile_properties_id[i].properties)
      ts->tile_properties[j++] = &ts->tile_properties_id[i];
  return (true);

 DeleteTileProperties:
  if (ts->tile_properties_id)
    {
      for (i = 0; i < ts->nbr_tiles; ++i)
	if (ts->tile_properties_id[i].properties)
	  bunny_delete_string_map(ts->tile_properties_id[i].properties);
      bunny_release(&ts->tile_properties_id);
    }
  if (ts->tile_properties)
    bunny_release(&ts->tile_properties);
 DeleteProperties:
  bunny_delete_string_map(ts->properties);
  ts->properties = NULL;
 DeleteAnimatedTiles:
  for (i = 0; i < ts->nbr_animated_tiles; ++i)
    if (ts->animated_tiles[i])
      {
	bunny_delete_clipable(&ts->animated_tiles[i]->clipable);
	ts->animated_tiles[i] = NULL;
      }
  bunny_free(ts->animated_tiles);
  ts->animated_tiles = NULL;
 DeletePicture:
  bunny_delete_clipable(ts->tileset);
  ts->tileset = NULL;
 DeleteName:
  bunny_free((char*)ts->name);
  ts->name = NULL;
  return (false);
}

static bool		load_layer(t_bunny_configuration			*cnf,
				   struct bunny_tilemap				*tmap,
				   t_bunny_tile_layer				*layer)
{
  if (tmap->method != BTM_VECTOR)
    {
      if ((layer->picture = bunny_new_picture(tmap->width, tmap->height)) == NULL)
	return (false);
    }
  else
    layer->picture = NULL;

  if (!bunny_configuration_getf_bool(cnf, &layer->visible, "Visible"))
    layer->visible = true;

  if (!bunny_configuration_getf_string(cnf, &layer->name, "Name"))
    layer->name = "";
  if (!(layer->name = bunny_strdup(layer->name)))
    return (false);

  layer->nbr_tiles = tmap->map_size.x * tmap->map_size.y;
  if (layer->nbr_tiles != bunny_configuration_casesf(cnf, "Tiles"))
    goto DeleteName;

  if (!(layer->tiles = (int*)bunny_calloc(layer->nbr_tiles, sizeof(int))))
    goto DeleteName;
  int			i;

  for (i = 0; bunny_configuration_getf_int(cnf, &layer->tiles[i], "Tiles[%d]", i); ++i);
  if (i != layer->nbr_tiles)
    goto DeleteTiles;

  if (bunny_color_configuration("ColorMask", &layer->color_mask, cnf) == BD_ERROR)
    goto DeleteTiles;

  // Custom properties
  t_bunny_configuration	*nod;

  if (bunny_configuration_getf_node(cnf, &nod, "Properties"))
    if (!load_properties(nod, &layer->properties))
      goto DeleteTiles;

  return (true);
 DeleteTiles:
  bunny_free((char*)layer->tiles);
 DeleteName:
  bunny_free((char*)layer->name);
  return (false);
}

t_bunny_tilemap		*__bunny_load_dabsic_tilemap(t_bunny_configuration	*conf,
						     struct bunny_tilemap	*tmap)
{
  t_bunny_configuration	*map;
  t_bunny_configuration	*nod;
  int			i, j;

  // Check the map node
  if (!bunny_configuration_getf_node(conf, &map, "Tilemap"))
    return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->map_size.x, "Width"))
    if (!bunny_configuration_getf_int(map, &tmap->map_size.x, "MapWidth"))
      if (!bunny_configuration_getf_int(map, &tmap->map_size.x, "Size[0]"))
	if (!bunny_configuration_getf_int(map, &tmap->map_size.x, "MapSize[0]"))
	  return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->map_size.y, "Height"))
    if (!bunny_configuration_getf_int(map, &tmap->map_size.y, "MapHeight"))
      if (!bunny_configuration_getf_int(map, &tmap->map_size.y, "Size[1]"))
	if (!bunny_configuration_getf_int(map, &tmap->map_size.y, "MapSize[1]"))
	  return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->tile_size.x, "TileWidth"))
    if (!bunny_configuration_getf_int(map, &tmap->tile_size.x, "TileSize[0]"))
      return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->tile_size.y, "TileHeight"))
    if (!bunny_configuration_getf_int(map, &tmap->tile_size.y, "TileSize[1]"))
      return (NULL);

  // Retrieve how tiles'gonna be displayed
  const char		*str;

  if (!bunny_configuration_getf_string(map, &str, "Projection"))
    str = "";
  if (!bunny_strcasecmp(str, "Perspective"))
    tmap->projection = BTP_PERSPECTIVE;
  else if (!bunny_strcasecmp(str, "Isometric"))
    tmap->projection = BTP_ISOMETRIC;
  else if (!bunny_strcasecmp(str, "Parrallel"))
    tmap->projection = BTP_PERSPECTIVE;
  else
    tmap->projection = BTP_FLAT;

  if (!bunny_configuration_getf_string(map, &str, "Method"))
    str = "";
  if (!bunny_strcasecmp(str, "Layer"))
    tmap->method = BTM_LAYER;
  else if (!bunny_strcasecmp(str, "Vector"))
    tmap->method = BTM_VECTOR;
  else
    tmap->method = BTM_FLAT;

  // Count layers and tilesets
  tmap->nbr_tilesets = bunny_configuration_casesf(map, "Tilesets");
  tmap->nbr_layers = bunny_configuration_casesf(map, "Layers");

  // Load tileset
  if (!(tmap->tilesets = (t_bunny_tileset*)bunny_calloc
	(tmap->nbr_tilesets, sizeof(*tmap->tilesets))))
    return (NULL);
  for (i = 0; bunny_configuration_getf_node(map, &nod, "Tilesets[%d]", i); ++i)
    if (load_tileset(nod, tmap, &tmap->tilesets[i]) == false)
      goto DeleteTilesets;
  // Set first and last_tile
  if ((j = tmap->tilesets[0].first_tile) == -1)
    j = 1;
  for (i = 0; i < tmap->nbr_tilesets; ++i)
    {
      tmap->tilesets[i].first_tile = j;
      tmap->tilesets[i].last_tile = tmap->tilesets[i].nbr_tiles + j;
      j += 1;
    }

  // Load layer
  if (!(tmap->layers = (t_bunny_tile_layer*)bunny_calloc
	(tmap->nbr_layers, sizeof(*tmap->layers))))
    goto DeleteTilesets;
  for (i = 0; bunny_configuration_getf_node(map, &nod, "Layers[%d]", i); ++i)
    if (load_layer(nod, tmap, &tmap->layers[i]) == false)
      goto DeleteLayers;

  // Load tilemap initial runtime configuration
  if (!bunny_configuration_getf_double(map, &tmap->camera.x, "Camera[0]"))
    bunny_configuration_getf_double(map, &tmap->camera.x, "Camera.X");
  if (!bunny_configuration_getf_double(map, &tmap->camera.y, "Camera[1]"))
    bunny_configuration_getf_double(map, &tmap->camera.y, "Camera.Y");

  if (!bunny_configuration_getf_double(map, &tmap->zoom.x, "Zoom[0]"))
    bunny_configuration_getf_double(map, &tmap->zoom.x, "Zoom.X");
  if (!bunny_configuration_getf_double(map, &tmap->zoom.y, "Zoom[0]"))
    bunny_configuration_getf_double(map, &tmap->zoom.y, "Zoom.Y");

  if (!bunny_configuration_getf_bool(map, &tmap->loop[0], "Loop[0]"))
    bunny_configuration_getf_bool(map, &tmap->loop[0], "Loop.X");
  if (!bunny_configuration_getf_bool(map, &tmap->loop[1], "Loop[1]"))
    bunny_configuration_getf_bool(map, &tmap->loop[1], "Loop.Y");

  bunny_configuration_getf_bool(map, &tmap->lock_borders, "LockBorders");
  bunny_configuration_getf_int(map, &tmap->layer_clip[0], "LayerClip[0]");
  bunny_configuration_getf_int(map, &tmap->layer_clip[1], "LayerClip[1]");
  bunny_configuration_getf_double(map, &tmap->rotation, "Rotation");

  // Custom properties
  if (bunny_configuration_getf_node(map, &nod, "Properties"))
    if (!load_properties(nod, &tmap->properties))
      goto DeleteLayers;

  return ((t_bunny_tilemap*)tmap);

 DeleteLayers:
  for (i = 0; i < tmap->nbr_layers; ++i)
    bunny_delete_layer(&tmap->layers[i]);
  bunny_free(tmap->layers);
 DeleteTilesets:
  for (i = 0; i < tmap->nbr_tilesets; ++i)
    bunny_delete_tileset(&tmap->tilesets[i]);
  bunny_free(tmap->tilesets);
  return (NULL);
}

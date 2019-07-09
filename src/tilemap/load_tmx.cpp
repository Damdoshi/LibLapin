// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// Bibliothèque Lapin

#include		"lapin_private.h"

#define			PATTERN		"%p configuration, %p tilemap -> %p"

static bool		assert_node_value(t_bunny_configuration			*cnf,
					  const char				*addr,
					  const char				*val)
{
  const char		*tmp;

  if (!bunny_configuration_getf_string(cnf, &tmp, addr))
    return (false);
  return (strcmp(tmp, val) == 0);
}

static bool		load_animation(t_bunny_configuration			*cnf,
				       struct bunny_tilemap			*tmap,
				       const char				*file,
				       t_bunny_tileset				*ts)
{
  std::stringstream	ss;
  t_bunny_configuration	*nod;
  int			i, j, tile;

  // How many tiles exists?
  ts->nbr_animated_tiles = 0;
  for (i = 0; bunny_configuration_getf_node(cnf, &nod, "[%d]", i); ++i)
    if (!strcmp(bunny_configuration_get_name(nod), "tile"))
      ts->nbr_animated_tiles += 1;
  // Create a short array
  if (!(ts->animated_tiles = (t_bunny_sprite**)bunny_calloc
	(ts->nbr_animated_tiles, sizeof(*ts->animated_tiles))))
    return (false);
  // Create a long array with key matching tile id (minus 1)
  if (!(ts->animated_tiles_id = (t_bunny_sprite**)bunny_calloc
	(ts->nbr_tiles, sizeof(*ts->animated_tiles))))
    goto DeleteAnimatedTiles;

  j = 0;
  for (i = 0; bunny_configuration_getf_node(cnf, &nod, "[%d]", i); ++i)
    if (!strcmp(bunny_configuration_get_name(nod), "tile"))
      {
	t_bunny_configuration *anim, *frame;
	t_bunny_sprite	*atile;

	// Retrieve the animated tile id or ignore the current node
	if (!bunny_configuration_getf_int(nod, &tile, "id"))
	  continue ;
	// Check there an animation here
	if (!bunny_configuration_get_case_named(nod, &anim, "animation"))
	  continue ;

	// Forge a bunny sprite configuration
	ss << "RessourceFile = \"" << file << "\"\n"
	   << "InitialAnimation = \"A0\"\n"
	   << "Frequency = 1000\n"
	   << "Intertile = " << ts->intertile.x << ", " << ts->intertile.y << "\n"
	   << "[Clip\n"
	   << "  Size = " << tmap->tile_size.x << ", " << tmap->tile_size.y << "\n"
	   << "  Selected = 0\n"
	   << "]\n"
	   << "[Animations\n";

	for (size_t k = 0; bunny_configuration_getf_node(anim, &frame, "[%zu]", k); ++k)
	  {
	    char	next[16];
	    int		x, y, delay, tileid;

	    if (!bunny_configuration_getf_int(frame, &tileid, "tileid"))
	      goto DeleteAnimatedTilesId;
	    if (!bunny_configuration_getf_int(frame, &delay, "duration"))
	      goto DeleteAnimatedTilesId;
	    if (k + 1 >= bunny_configuration_get_nbr_case(anim))
	      snprintf(&next[0], sizeof(next), "A0");
	    else
	      snprintf(&next[0], sizeof(next), "A%zu", k + 1);
	    x = (tileid % ts->tileset_size.x) * (ts->tile_size.x + ts->intertile.x);
	    y = (tileid / ts->tileset_size.x) * (ts->tile_size.y + ts->intertile.y);
	    ss << "  [A" << k << "\n"
	       << "    Frame = 1\n"
	       << "    Position = " << x << ", " << y << "\n"
	       << "    NextAnimation = \"" << &next[0] << "\"\n"
	       << "    {FramePlay\n"
	       << "      " << delay << "\n"
	       << "    }\n"
	       << "  ]\n";
	  }
	ss << "]\n";
	printf("%s\n", ss.str().c_str());

	// Parse the configuration
	if (!(nod = bunny_read_configuration(BC_DABSIC, ss.str().c_str(), NULL)))
	  goto DeleteAnimatedTilesId;
	// Generate the bunny sprite
	atile = bunny_read_sprite(nod);
	bunny_delete_configuration(nod);
	if (atile == NULL)
	  goto DeleteAnimatedTilesId;
	// Check if id is duplicated
	if (ts->animated_tiles_id[tile])
	  {
	    bunny_delete_clipable(&atile->clipable);
	    goto DeleteAnimatedTilesId;
	  }

	// Save the bunny sprite
	ts->animated_tiles_id[tile] = atile;
	ts->animated_tiles[j] = atile;
	j += 1;
      }

  return (true);

 DeleteAnimatedTilesId:
  bunny_free(ts->animated_tiles_id);
 DeleteAnimatedTiles:
  for (i = 0; i < ts->nbr_animated_tiles; ++i)
    if (ts->animated_tiles[i])
      bunny_delete_clipable(&ts->animated_tiles[i]->clipable);
  bunny_free(ts->animated_tiles);
  return (false);
}

static bool		load_properties(t_bunny_configuration			*cnf,
					t_bunny_map				**_map)
{
  t_bunny_configuration	*props;
  t_bunny_map		*map;

  if ((map = *_map = bunny_new_map(string_map)) == NULL)
    return (false);
  for (int i = 0; bunny_configuration_getf_node(cnf, &props, "[%d]", i); ++i)
    {
      const char	*k, *d;

      if (!bunny_configuration_getf_string(props, &k, "name"))
	goto DeleteMap;
      if (!bunny_configuration_getf_string(props, &d, "value"))
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
  if (!bunny_configuration_getf_string(cnf, &ts->name, "name"))
    return (false);

  // Tile info
  if (!bunny_configuration_getf_int(cnf, &ts->tile_size.x, "tilewidth"))
    ts->tile_size.x = tmap->tile_size.x;
  if (!bunny_configuration_getf_int(cnf, &ts->tile_size.y, "tileheight"))
    ts->tile_size.y = tmap->tile_size.y;

  // Intertile
  // bunny_configuration_getf_int(cnf, &ts->margin.x, "margin");
  // bunny_configuration_getf_int(cnf, &ts->margin.y, "margin");
  bunny_configuration_getf_int(cnf, &ts->intertile.x, "spacing");
  bunny_configuration_getf_int(cnf, &ts->intertile.y, "spacing");
  ts->margin.x = ts->intertile.x;
  ts->margin.y = ts->intertile.y;

  // First and last tile
  if (!bunny_configuration_getf_int(cnf, &ts->nbr_tiles, "tilecount"))
    return (false);
  if (!bunny_configuration_getf_int(cnf, &ts->first_tile, "firstgid"))
    return (false);

  // Misc
  if (!(ts->name = bunny_strdup(ts->name)))
    return (false);

  // Picture
  t_bunny_configuration	*nod;
  const char		*tmp;

  if (!bunny_configuration_get_case_named(cnf, &nod, "image"))
    goto DeleteName;

  if (!bunny_configuration_getf_string(nod, &tmp, "source"))
    goto DeleteName;
  if (!(ts->tileset = bunny_load_picture(tmp)))
    goto DeleteName;
  ts->tileset_size.x = ts->tileset->buffer.width / ts->tile_size.x;
  ts->tileset_size.y = ts->tileset->buffer.height / ts->tile_size.y;
  if (load_animation(cnf, tmap, tmp, ts) == false)
    goto DeletePicture;

  // Check everything is okay.
  int			i;

  if (!bunny_configuration_getf_int(nod, &i, "width"))
    goto DeleteAnimated;
  if (i != ts->tileset->buffer.width)
    goto DeleteAnimated;
  if (!bunny_configuration_getf_int(nod, &i, "height"))
    goto DeleteAnimated;
  if (i != ts->tileset->buffer.height)
    goto DeleteAnimated;

  // Deduce last values
  ts->last_tile = ts->first_tile + ts->nbr_tiles;

  // Custom tileset properties
  if (bunny_configuration_get_case_named(cnf, &nod, "properties"))
    if (!load_properties(nod, &ts->properties))
      goto DeleteAnimated;

  return (true);

 DeleteAnimated:
  for (int i = 0; i < ts->nbr_tiles; ++i)
    if (ts->animated_tiles[i])
      bunny_delete_clipable(&ts->animated_tiles[i]->clipable);
  bunny_free(ts->animated_tiles);
 DeletePicture:
  bunny_delete_clipable(ts->tileset);
 DeleteName:
  bunny_free((char*)ts->name);
  return (false);
}

static bool		load_layer(t_bunny_configuration			*cnf,
				   struct bunny_tilemap				*tmap,
				   t_bunny_tile_layer				*layer)
{
  if (!bunny_configuration_getf_bool(cnf, &layer->visible, "visible"))
    layer->visible = true;
  if (!bunny_configuration_getf_int(cnf, &layer->size.x, "width"))
    layer->size.x = tmap->map_size.x;
  if (!bunny_configuration_getf_int(cnf, &layer->size.y, "height"))
    layer->size.y = tmap->map_size.y;

  if (!bunny_configuration_getf_string(cnf, &layer->name, "name"))
    return (false);
  if (!(layer->name = bunny_strdup(layer->name)))
    return (false);
  t_bunny_configuration	*nod;

  if (!bunny_configuration_get_case_named(cnf, &nod, "data"))
    return (false);
  const char		*encoding;
  const char		*data;
  size_t		datalen;

  if (!bunny_configuration_getf_string(nod, &encoding, "encoding"))
    goto DeleteName;
  if (strcmp(encoding, "base64"))
    goto DeleteName;

  if (!bunny_configuration_getf_string(nod, &data, "[0]"))
    goto DeleteName;
  if (!bunny_base64_decode(data, strlen(data), (void**)&layer->tiles, &datalen))
    goto DeleteName;
  datalen /= sizeof(int);
  if (datalen != (size_t)(layer->size.x * layer->size.y))
    goto DeleteData;
  layer->nbr_tiles = datalen;
  double		v;

  layer->color_mask.full = WHITE;
  if (bunny_configuration_getf_double(cnf, &v, "opacity"))
    layer->color_mask.argb[ALPHA_CMP] = bunny_clamp(v, 0.0, 1.0) * 255;

  // Custom layer properties
  if (bunny_configuration_get_case_named(cnf, &nod, "properties"))
    if (!load_properties(nod, &layer->properties))
      goto DeleteData;

  return (true);

 DeleteData:
  bunny_free(layer->tiles);
 DeleteName:
  bunny_free((char*)layer->name);
  return (false);
}

t_bunny_tilemap		*__bunny_load_tmx_tilemap(t_bunny_configuration		*conf,
						  struct bunny_tilemap		*tmap)
{
  const char		*required_fields[][2] = {
    {"version", "1.0"},
    {"orientation", "orthogonal"},
    {"renderorder", "left-up"}
  };
  t_bunny_configuration	*map;
  t_bunny_configuration	*nod;
  size_t		i, j;

  // Check the map node
  if (!bunny_configuration_getf_node(conf, &map, "[0]"))
    return (NULL);
  if (strcmp(bunny_configuration_get_name(map), "map"))
    return (NULL);
  for (i = 0; i < NBRCELL(required_fields); ++i)
    if (!assert_node_value(map, required_fields[i][0], required_fields[i][1]))
      return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->map_size.x, "width"))
    return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->map_size.y, "height"))
    return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->tile_size.x, "tilewidth"))
    return (NULL);
  if (!bunny_configuration_getf_int(map, &tmap->tile_size.y, "tileheight"))
    return (NULL);

  // Count layers and tilesets
  tmap->nbr_tilesets = 0;
  tmap->nbr_layers = 0;
  for (bunny_configuration_all_cases(map, i))
    if (!bunny_configuration_getf_node(map, &nod, "[%zu]", i))
      return (NULL);
    else if (!strcmp(bunny_configuration_get_name(nod), "tileset"))
      tmap->nbr_tilesets += 1;
    else if (!strcmp(bunny_configuration_get_name(nod), "layer"))
      tmap->nbr_layers += 1;

  // Load tileset
  if (!(tmap->tilesets = (t_bunny_tileset*)bunny_calloc
	(tmap->nbr_tilesets, sizeof(*tmap->tilesets))))
    return (NULL);
  for (j = 0, bunny_configuration_all_cases(map, i))
    if (!bunny_configuration_getf_node(map, &nod, "[%zu]", i))
      goto DeleteTilesets;
    else if (!strcmp(bunny_configuration_get_name(nod), "tileset"))
      if (load_tileset(nod, tmap, &tmap->tilesets[j++]) == false)
	goto DeleteTilesets;

  // Load layers
  if (!(tmap->layers = (t_bunny_tile_layer*)bunny_calloc
	(tmap->nbr_layers, sizeof(*tmap->layers))))
    goto DeleteTilesets;
  for (j = 0, bunny_configuration_all_cases(map, i))
    if (!bunny_configuration_getf_node(map, &nod, "[%zu]", i))
      goto DeleteLayers;
    else if (!strcmp(bunny_configuration_get_name(nod), "layer"))
      if (load_layer(nod, tmap, &tmap->layers[j++]) == false)
	goto DeleteLayers;

  // Custom map properties
  if (bunny_configuration_get_case_named(map, &nod, "properties"))
    if (!load_properties(nod, &tmap->properties))
      goto DeleteLayers;

  return ((t_bunny_tilemap*)tmap);

 DeleteLayers:
  for (i = 0; i < (size_t)tmap->nbr_layers; ++i)
    bunny_delete_layer(&tmap->layers[i]);
  bunny_free(tmap->layers);
 DeleteTilesets:
  for (i = 0; i < (size_t)tmap->nbr_tilesets; ++i)
    bunny_delete_tileset(&tmap->tilesets[i]);
  bunny_free(tmap->tilesets);
  return (NULL);
}


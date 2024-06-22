typedef struct			s_bunny_tile_property
{
  // From configuration
  t_bunny_map			*properties; // map[string] = string
  // For runtime
  char				custom[64];
}				t_bunny_tile_property;

/*
** - Filling and clearing a tilemap fill and clear the whole.
** - Setting shape onn a tilemap draw on the final clipable
** - Blitting to a tilemap place the picture at a specific position
**   depending of the tilemap itself.
*/
# ifdef				__MINGW32__
#  pragma			pack(1)
# endif

typedef struct			s_bunny_tileset
{
  const char			*name;
  t_bunny_picture		*tileset;
  t_bunny_size			tile_size;
  t_bunny_size			margin;
  t_bunny_size			intertile;
  t_bunny_size			tileset_size;
  t_bunny_sprite		**animated_tiles_id; // nbr_tiles length
  t_bunny_tile_property		*tile_properties_id; // nbr_tiles length
  int				nbr_tiles;
  t_bunny_tile_property		**tile_properties; // nbr_tile_properties length
  int				nbr_tile_properties;
  t_bunny_sprite		**animated_tiles; // nbr_animated_tiles length
  int				nbr_animated_tiles;
  int				first_tile;
  int				last_tile;

  t_bunny_map			*properties;
}				t_bunny_tileset;

typedef struct			s_bunny_tile_layer
{
  bool				visible;
  const char			*name;
  t_bunny_size			size;
  int				*tiles;
  int				nbr_tiles;
  t_bunny_color			color_mask;

  t_bunny_map			*properties;
}				t_bunny_tile_layer;

typedef struct			s_bunny_tilemap
{
  // The t_bunny_tilemap is a clipable
  t_bunny_clipable		clipable;
  const size_t			_private[3];

  // Tile size in pixels
  const t_bunny_size		tile_size;
  // Size of map in tiles
  const t_bunny_size		map_size;

  // Tilesets
  t_bunny_tileset * const	tilesets;
  const int			nbr_tilesets;

  // Tiles
  t_bunny_tile_layer * const	layers;
  const int			nbr_layers;

  // Display layers only between layer_clip[0] and layer_clip[1]
  int				layer_clip[2];

  t_bunny_accurate_position	camera;
  t_bunny_accurate_position	zoom;
  double			rotation;
  bool				lock_borders;
  bool				loop[2];

  t_bunny_map			*properties;
}				t_bunny_tilemap;
# pragma			pack()

t_bunny_tilemap			*bunny_load_tilemap_wh(const char			*cnf,
						       unsigned int			width,
						       unsigned int			height);

t_bunny_tilemap			*bunny_load_tilemap(const char				*cnf);

int				bunny_tilemap_get_tile_from_px(const t_bunny_tilemap	*tmap,
							       const t_bunny_position	*pos,
							       int			z);

int				bunny_tilemap_get_tile(const t_bunny_tilemap		*tmap,
						       const t_bunny_position		*pos,
						       int				z);
t_bunny_tile_property		*bunny_tilemap_get_properties(const t_bunny_tilemap	*tmap,
							      const t_bunny_position	*pos,
							      int			z);
t_bunny_tile_property		*bunny_tilemap_get_properties_from_px(const t_bunny_tilemap *tmap,
								      const t_bunny_position *pos,
								      int		z);

t_bunny_tilemap			*bunny_tilemap_new_viewpoint(t_bunny_tilemap		*tm,
							     unsigned int		width,
							     unsigned int		height);

void				bunny_tilemap_set_camera(t_bunny_tilemap		*map,
							 t_bunny_accurate_position	pos);

t_bunny_tileset			*bunny_get_tileset_for_tile(const t_bunny_tilemap	*map,
							    int				tile);

typedef bool			(*t_bunny_tile_property_func)(t_bunny_tilemap		*tmap,
							      t_bunny_tileset		*set,
							      t_bunny_tile_property	*p,
							      void			*data);
bool				bunny_browse_tile_properties(t_bunny_tilemap		*tmap,
							     t_bunny_tile_property_func	f,
							     void			*dat);

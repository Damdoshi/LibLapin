/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_TILEMAP_H__
# define			__LAPIN_TILEMAP_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

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
#  pragma			pack(4)
# endif

// The picture that contains tiles
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

t_bunny_tileset			*bunny_load_tileset(const char			*s);
t_bunny_tileset			*bunny_read_tileset(t_bunny_configuration	*cnf);
t_bunny_configuration		*bunny_save_tileset(t_bunny_tileset		*ts,
						    t_bunny_configuration	*cnf);

typedef struct			s_bunny_tile_layer
{
  bool				visible;
  const char			*name;
  int				*tiles;
  int				nbr_tiles;
  t_bunny_color			color_mask;

  t_bunny_picture		*picture;
  t_bunny_map			*properties;
}				t_bunny_tile_layer;

typedef enum			e_bunny_tilemap_projection
  {
    BTP_FLAT,
    BTP_PARRALLEL,		// Not implemented
    BTP_ISOMETRIC,		// Not implemented
    BTP_PERSPECTIVE
  }				t_bunny_tilemap_projection;

typedef enum			e_bunny_tilemap_method
  {
    BTM_FLAT,
    BTM_LAYER,
    BTM_VECTOR			// Not implemented
  }				t_bunny_tilemap_method;

// The objet to be drawn that use tilesets as ressources
typedef struct			s_bunny_tilemap
{
  // The t_bunny_tilemap is a clipable
  t_bunny_clipable		clipable;
  const size_t			_private[3];

  // Display mode. Default is BTR_FLAT | BTR_2D
  bool				normal_map;
  t_bunny_tilemap_projection	projection;
  t_bunny_tilemap_method	method;

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

  // Display layers only between layer_clip[0] and layer_clip[1].
  // If depth projection is used, layer_clip are relative to camera.z
  int				layer_clip[2];

  t_bunny_accurate_zposition	camera;
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

t_bunny_configuration		*bunny_save_tilemap(t_bunny_tilemap			*tmap,
						    t_bunny_configuration		*cnf);

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

#endif	/*			__LAPIN_TILEMAP_H__					*/

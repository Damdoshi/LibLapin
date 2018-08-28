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

/*
** - Filling and clearing a tilemap fill and clear the whole.
** - Setting shape onn a tilemap draw on the final clipable
** - Blitting to a tilemap place the picture at a specific position
**   depending of the tilemap itself.
*/

# ifdef				__MINGW32__
#  pragma			pack(1)
# endif
typedef struct			s_bunny_tilemap
{
  // The t_bunny_tilemap is a clipable
  t_bunny_clipable		clipable;
  size_t			_private[3];

  // Those properties apply to tiles displayed *inside* the clipable
  int				layer_clip[2];
  const int			nbr_layers;
  const t_bunny_size		map_size;
  int * const			tiles;
  const t_bunny_size		tile_size;
  t_bunny_accurate_position	camera;
  t_bunny_accurate_position	zoom;
  double			rotation;
  int				lock_borders;
  bool				loop[2];
}				t_bunny_tilemap;
# pragma			pack()

t_bunny_tilemap			*bunny_load_tilemap_wh(const char	*cnf,
						       unsigned int	width,
						       unsigned int	height);

t_bunny_tilemap			*bunny_load_tilemap(const char		*cnf);

int				bunny_tilemap_get_tile_from_px(const t_bunny_tilemap *tmap,
							       const t_bunny_position *pos);

int				bunny_tilemap_get_tile(const t_bunny_tilemap *tmap,
						       const t_bunny_position *pos);

/*
** Does not exploit all properties of light: it only serves to product a *shadow*
** drawing on dest.
**
** It only exploits active, x, y and ligth_attenuation.
** Light color could be exploited too, as ambient color properties, but I do not
** want to decide how yet.
**
** Two colors are currently supported by tilemap raytrace: opaque black and
** else. alpha full white may be used later to create reflexion.
** Tiles that are zero are considered full transparent. Other are tested pixel
** per pixel.
**
** bunny_tilemap_raytrace does not blacken the sent pixelarray at start.
** It is up to you to do it.
**
**
** Technically, this function only increase pixel transparency after light
** emission...
** This function also render the tilemap. This is why tmap is not const.
*/
bool				bunny_tilemap_raytrace(t_bunny_tilemap *tmap,
						       int		layer,
						       const t_bunny_normal_light *lights,
						       size_t		nbr_light,
						       t_bunny_picture	*dest,
						       double		light_str);

typedef bool			(*t_my_tile_collide)(int		tile,
						     int		x,
						     int		y,
						     int		tx,
						     int		ty);
extern t_my_tile_collide	gl_bunny_my_tile_collide;

#endif	/*			__LAPIN_TILEMAP_H__			*/

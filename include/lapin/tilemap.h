/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2017
**
** Bibliotheque Lapin
*/

/*!
** \file tilemap.h
** Module to load and exploit Tiled Editor level format.
** All features may not be supported.
** Supported and unsupported features will be notified
** along this documentation.
*/

#ifndef			__LAPIN_TILEMAP_H__
# define		__LAPIN_TILEMAP_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif

/*!
**
** Isometric, staggered and hexagonal and not supported yet.
*/
typedef enum		e_bunny_tilemap_orientation
  {
    BTO_ORTHOGONAL,
    BTO_ISOMETRIC,
    BTO_STAGGERED,
    BTO_HEXAGONAL
  }			t_bunny_tilemap_orientation;

/*!
**
** Only right down is currently supported
*/
typedef enum		e_bunny_tilemap_render_order
  {
    BTRO_RIGHT_DOWN,
    BTRO_RIGHT_UP,
    BTRO_LEFT_DOWN,
    BTRO_LEFT_UP
  }			t_bunny_tilemap_render_order;

/*!
**
*/
typedef struct		s_bunny_tileset
{
  int			first_gid;
  // tsx file ?
  const char		*name; // => inutile
  t_bunny_size		tile_size;
  t_bunny_size		size_tin_tile;
  int			tile_spacing; // ? C'est quoi la diff entre les deux?
  int			tile_margin; // ?
}			t_bunny_tileset;

/*!
**
*/
typedef struct		s_bunny_tilemap
{
  t_bunny_vector	*tilesets; // vector of t_bunny_tileset
  t_bunny_map		*terrains; // [name] = configuration
  t_bunny_map		*animation;
  t_bunny_tilemap_orientation orientation;
  t_bunny_tilemap_render_order render_order;
  t_bunny_size		size_in_tile;
  t_bunny_size		tile_size;
  t_bunny_size		size_in_pixel;
  t_bunny_color		background_color;
}			t_bunny_tilemap;

typedef struct		s_bunny_tilemap_status
{
  t_bunny_position	tile_offset;
  int			animation;
  double		current_time;
}			t_bunny_tilemap_status;

/*!
**
*/
t_bunny_tilemap		*bunny_load_tilemap(const char			*cnffile);

/*!
**
*/
void			buny_delete_tilemap(t_bunny_tilemap		*tmap);

/*!
** Handle zoom. (Rotation must be realized by rotating target)
*/
void			bunny_draw_tilemap(t_bunny_buffer		*target,
					   const t_bunny_tilemap	*map,
					   const t_bunny_tilemap_status	*status);

/*!
**
*/
void			bunny_animate_tilemap(const t_bunny_tilemap	*map,
					      t_bunny_tilemap_status	*status,
					      double			elapsed);

#endif	/*		__LAPIN_TILEMAP_H__				*/

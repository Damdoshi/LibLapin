/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2020
**
** Bibliotheque Lapin
*/

#ifndef			__LAPIN_TILESET_H__
# define		__LAPIN_TILESET_H__
# if			!defined(__LAPIN_H__)
#  error		You cannot include this file directly.
# endif
/*
typedef struct		s_bunny_tileset
{
  const char		*name;			// The name of the tileset
  t_bunny_picture	*tileset;		// The pixels of the tileset
  int			first_tile;		// L'id le plus bas. Minimum 1.
  int			last_tile;		// L'id le plus haut.

  t_bunny_size		tile_size;		// La taille d'une seule tuile.
  t_bunny_size		margin;			// La marge avec le coin supérieur gauche
  t_bunny_size		intertile;		// L'espace entre les tuiles
  t_bunny_size		tileset_size;		// Le nombre de tuile sur X/Y.

  t_bunny_map		*animated_tiles;	// [int id_tuile] -> t_bunny_sprite*
  t_bunny_map		*tile_properties;	// [int id_tuile] -> t_bunny_configuration*
  t_bunny_configuration	*properties;		// Les propriétés du tileset
  const bool		proper_configuration;	// Est ce que les configurations ne sont pas externes?
}			t_bunny_tileset;

t_bunny_tileset		*bunny_load_tileset(const char				*s);
t_bunny_tileset		*bunny_read_tileset(t_bunny_configuration		*cnf,
					    const char				*pattern,
					    ...);
t_bunny_configuration	*bunny_write_tileset(const t_bunny_tileset		*ts,
					     t_bunny_configuration		*cnf);
bool			bunny_save_tileset(const t_bunny_tileset		*ts,
					   const char				*file);

// Prepare clip for specified tile. Return NULL if tile is incorrect.
const t_bunny_picture	*bunny_tileset_get_tile(t_bunny_tileset			*ts,
						int				tile);
// Just return the configuration. Create it if it does not exist.
t_bunny_configuration	*bunny_tileset_get_property(t_bunny_tileset		*ts,
						    int				tile);

void			bunny_delete_tileset(t_bunny_tileset			*ts);
*/
#endif	/*		__LAPIN_TILESET_H__					*/

/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** Bibliotheque Lapin
*/

#ifndef				__LAPIN_PARALLAX_H__
# define			__LAPIN_PARALLAX_H__
# if				!defined(__LAPIN_H__)
#  error			You cannot include this file directly.
# endif

/*
** A quoi peut servir parallax?
** A afficher des images plus grandes qu'un espace défini en scrollant a des vitesses variables
** A afficher des images plus grandes meme sur une seule dimension en scrollant a des vitesses variables
** A afficher un fond propre a la camera.
**
** Il est possible de demander à étirer une image de differentes manières, en ce cas, elle occupe
** precisemment la taille en question pour le coté parallax, mais un scale specifique sera tout de meme
** appliqué si écrit.
** L'étirage double (vertical et horizontal) implique une absence de parallax si l'echelle de base
** est utilisée. Sinon cela provoque un agrandissement du facteur de l'espace a remplir et l'effet parallax
**
** (En somme, il faut toujours un effet parallax après coup)
*/

typedef enum			e_bunny_parallax_mode
  {
    BPM_CENTERED,		// Keep the original size.
    BPM_FILL,			// Keep ratio. Stretch to fill the entire window
    BPM_MAXIMIZED,		// Keep ratio. Stretch to fill the best without overflowing
    BPM_STRETCHED		// Don't keep ratio. Stretch.
  }				t_bunny_parallax_mode;

typedef struct			s_bunny_parallax_layer
{
  t_bunny_picture		*picture;
  t_bunny_parallax_mode		mode;		// Scale in a specific way the layer
  bool				local;		// Is mode applied to local or global space
  bool				loop_x;		// Ignored if mode is max or stretch
  bool				loop_y;		// Ignored if mode is max or stretch
  bool				speed_lock;	// Do not compute speed_ratio from size - for scrolling
  t_bunny_accurate_position	speed_ratio;	//
}				t_bunny_parallax_layer;

typedef struct			s_bunny_parallax
{
  t_bunny_clipable		clipable;
  size_t			_private[3];
  t_bunny_parallax_layer	*layers;
  size_t			nbr_layers;
  t_bunny_size			inside_size;
  t_bunny_accurate_position	viewpoint;
  bool				lock_viewpoint;
}				t_bunny_parallax;

t_bunny_parallax		*bunny_load_parallax_wh(const char		*file,
							unsigned int		width,
							unsigned int		height);
t_bunny_parallax		*bunny_load_parallax(const char			*file);

t_bunny_parallax		*bunny_read_parallax_wh(t_bunny_configuration	*cnf,
							unsigned int		width,
							unsigned int		height);
t_bunny_parallax		*bunny_read_parallax(t_bunny_configuration	*cnf);

#endif	/*			__LAPIN_PARALLAX_H__				*/

